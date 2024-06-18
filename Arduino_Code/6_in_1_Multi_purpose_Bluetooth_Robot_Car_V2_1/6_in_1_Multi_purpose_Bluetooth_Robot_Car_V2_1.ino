#include "IR_remote.h"
#include "keymap.h"

IRremote ir(3);

#include <Servo.h>

volatile char BLE_bit_temp;
String BLE_value;
String G_Bluetooth_value;
volatile int G_degree;
volatile int re_string_len;
volatile float Left_photosensitive;
volatile float Right_photosensitive;
volatile int Lightseeking_Degree;
volatile float f;
volatile int speed_value;
volatile int D_mix;
volatile int D_mid;
volatile int D_max;
volatile boolean Funtion_FLag;
volatile int G_string_len;
volatile int BLE_Change_SPEED;

Servo myservo;
float checkdistance() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(10);
  digitalWrite(12, LOW);
  float distance = pulseIn(13, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Ultrasonic_Avoidance() {
  Funtion_FLag = true;
  while (Funtion_FLag) {
    int Front_Distance = 0;
    int Left_Distance = 0;
    int Right_Distance = 0;
    int Right_IR_Value = 1;
    int Left_IR_Value = 1;
    Left_IR_Value = digitalRead(A1);
    Right_IR_Value = digitalRead(A2);
    Front_Distance = checkdistance();
    Serial.println(Front_Distance);
    if (Left_IR_Value == 0 && Right_IR_Value == 1) {
      digitalWrite(2,HIGH);
      analogWrite(5,255);
      digitalWrite(4,LOW);
      analogWrite(6,12);

    } else if (Left_IR_Value == 1 && Right_IR_Value == 0) {
      digitalWrite(2,HIGH);
      analogWrite(5,12);
      digitalWrite(4,LOW);
      analogWrite(6,255);
    } else {
      digitalWrite(2,HIGH);
      analogWrite(5,(4 * 22.5));
      digitalWrite(4,LOW);
      analogWrite(6,(4 * 22.5));

    }
    if (Front_Distance <= D_mid) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
      if (Front_Distance <= D_mix || Left_IR_Value == 0 && Right_IR_Value == 0) {
        digitalWrite(2,LOW);
        analogWrite(5,(4.5 * 22.5));
        digitalWrite(4,HIGH);
        analogWrite(6,(4.5 * 22.5));
        delay(300);
        digitalWrite(2,LOW);
        analogWrite(5,0);
        digitalWrite(4,HIGH);
        analogWrite(6,0);

      }
      myservo.write(165);
      delay(500);
      Serial.println(Left_Distance);
      delay(100);
      Left_Distance = checkdistance();
      myservo.write(15);
      delay(500);
      Serial.println(Right_Distance);
      delay(100);
      Right_Distance = checkdistance();
      myservo.write(90);
      if ((D_mix < Left_Distance && Left_Distance < D_max) && (D_mix < Right_Distance && Right_Distance < D_max)) {
        if (Right_Distance > Left_Distance) {
          digitalWrite(2,HIGH);
          analogWrite(5,(9 * 22.5));
          digitalWrite(4,HIGH);
          analogWrite(6,(9 * 22.5));
          delay(250);

        } else {
          digitalWrite(2,LOW);
          analogWrite(5,(9 * 22.5));
          digitalWrite(4,LOW);
          analogWrite(6,(9 * 22.5));
          delay(250);

        }

      } else if (D_mix < Left_Distance && Left_Distance < D_max || D_mix < Right_Distance && Right_Distance < D_max) {
        if (D_mix < Left_Distance && Left_Distance < D_max) {
          digitalWrite(2,LOW);
          analogWrite(5,(7 * 22.5));
          digitalWrite(4,LOW);
          analogWrite(6,(7 * 22.5));
          delay(250);

        } else if (D_mix < Right_Distance && Right_Distance < D_max) {
          digitalWrite(2,HIGH);
          analogWrite(5,(7 * 22.5));
          digitalWrite(4,HIGH);
          analogWrite(6,(7 * 22.5));
          delay(250);
        }
      } else if (Right_Distance < D_mix && Left_Distance < D_mix) {
        digitalWrite(2,HIGH);
        analogWrite(5,0);
        digitalWrite(4,LOW);
        analogWrite(6,(9 * 22.5));
        delay(510);
        digitalWrite(2,LOW);
        analogWrite(5,0);
        digitalWrite(4,HIGH);
        analogWrite(6,0);
      }
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
    BLE_value = "";
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if ('%' == String(BLE_value).charAt(0) && 'Q' == String(BLE_value).charAt(1)) {
      Funtion_FLag = false;
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
  }
}

void Ultrasonic_Follow() {
  Funtion_FLag = true;
  while (Funtion_FLag) {
    int Infrared_Trigger_Flag = 0;
    int Front_Distance = 0;
    int Left_Distance = 0;
    int Right_Distance = 0;
    int Right_IR_Value = 1;
    int Left_IR_Value = 1;
    Left_IR_Value = digitalRead(A1);
    Right_IR_Value = digitalRead(A2);
    Front_Distance = checkdistance();
    if (Front_Distance < 5 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,(3 * 25.5));
      digitalWrite(4,HIGH);
      analogWrite(6,(3 * 25.5));

    } else if (Front_Distance < 5 && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,(4 * 25.5));
      digitalWrite(4,HIGH);
      analogWrite(6,(0.056 * (4 * 255)));
    } else if (Front_Distance < 5 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,(0.056 * (4 * 255)));
      digitalWrite(4,HIGH);
      analogWrite(6,(4 * 25.5));
    } else if (Front_Distance < 5 && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,(3 * 25.5));
      digitalWrite(4,HIGH);
      analogWrite(6,(3 * 25.5));
    } else if (Front_Distance > 10 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,HIGH);
      analogWrite(5,(4 * 25.5));
      digitalWrite(4,LOW);
      analogWrite(6,(4 * 25.5));
    } else if (Front_Distance > 10 && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,(4 * 25.5));
      digitalWrite(4,LOW);
      analogWrite(6,(4 * 25.5));
    } else if (Front_Distance > 10 && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      digitalWrite(2,HIGH);
      analogWrite(5,(4 * 25.5));
      digitalWrite(4,HIGH);
      analogWrite(6,(4 * 25.5));
    } else if ((5 <= Front_Distance && Front_Distance <= 10) && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value == Infrared_Trigger_Flag)) {
      digitalWrite(2,HIGH);
      analogWrite(5,(4 * 25.5));
      digitalWrite(4,LOW);
      analogWrite(6,(0.056 * (4 * 25.5)));
    } else if ((5 <= Front_Distance && Front_Distance <= 10) && (Left_IR_Value == Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,HIGH);
      analogWrite(5,(0.056 * (4 * 25.5)));
      digitalWrite(4,LOW);
      analogWrite(6,(4 * 25.5));
    } else if ((5 <= Front_Distance && Front_Distance <= 10) && (Left_IR_Value != Infrared_Trigger_Flag && Right_IR_Value != Infrared_Trigger_Flag)) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    }
    BLE_value = "";
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if ('%' == String(BLE_value).charAt(0) && 'Q' == String(BLE_value).charAt(1)) {
      Funtion_FLag = false;
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
  }
}

void Infrared_Tracing() {
  Funtion_FLag = true;
  int Left_Tra_Value = 1;
  int Center_Tra_Value = 1;
  int Right_Tra_Value = 1;
  int Black = 1;
  int white = 0;
  while (Funtion_FLag) {
    Left_Tra_Value = digitalRead(7);
    Center_Tra_Value = digitalRead(8);
    Right_Tra_Value = digitalRead(9);
    if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {
      digitalWrite(2,HIGH);
      analogWrite(5,120);
      digitalWrite(4,LOW);
      analogWrite(6,120);

    } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {
      digitalWrite(2,LOW);
      analogWrite(5,120);
      digitalWrite(4,LOW);
      analogWrite(6,120);
    } else if (Left_Tra_Value == Black && (Center_Tra_Value != Black && Right_Tra_Value != Black)) {
      digitalWrite(2,LOW);
      analogWrite(5,80);
      digitalWrite(4,LOW);
      analogWrite(6,80);
    } else if (Left_Tra_Value != Black && (Center_Tra_Value != Black && Right_Tra_Value == Black)) {
      digitalWrite(2,HIGH);
      analogWrite(5,80);
      digitalWrite(4,HIGH);
      analogWrite(6,80);
    } else if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {
      digitalWrite(2,HIGH);
      analogWrite(5,120);
      digitalWrite(4,HIGH);
      analogWrite(6,120);
    } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else if (false) {
    }
    BLE_value = "";
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if ('%' == String(BLE_value).charAt(0) && 'Q' == String(BLE_value).charAt(1)) {
      Funtion_FLag = false;
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
  }
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void G_Drive() {
  Funtion_FLag = true;
  while (Funtion_FLag) {
    while (Serial.available() > 0) {
      G_Bluetooth_value = G_Bluetooth_value + ((char)(Serial.read()));
      delay(2);
    }
    if (0 < String(G_Bluetooth_value).length()) {
      Serial.println(G_Bluetooth_value);
      G_string_len = String(G_Bluetooth_value).length();
      if (G_string_len <= 7 && ('@' == String(G_Bluetooth_value).charAt(0) && '#' == String(G_Bluetooth_value).charAt((G_string_len - 2)))) {
        G_degree = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
        float value = (BLE_Change_SPEED / 10) * 16;
        double d_speed = 0.00;
        if (0 <= G_degree && G_degree <= 90) {
          d_speed = (mapfloat(G_degree, 0, 90, 0, 1));
          digitalWrite(2,HIGH);
          analogWrite(5,value);
          digitalWrite(4,LOW);
          analogWrite(6,(d_speed * value));

        } else if (90 < G_degree && G_degree <= 180) {
          d_speed = (mapfloat(G_degree, 180, 90, 0, 1));
          digitalWrite(2,HIGH);
          analogWrite(5,(d_speed * value));
          digitalWrite(4,LOW);
          analogWrite(6,value);
        } else if (-180 < G_degree && G_degree <= -90) {
          d_speed = (mapfloat(G_degree, (-180), (-90), 0, 1));
          digitalWrite(2,LOW);
          analogWrite(5,(d_speed * value));
          digitalWrite(4,HIGH);
          analogWrite(6,value);
        } else if (-90 < G_degree && G_degree < 0) {
          d_speed = (mapfloat(G_degree, (-90), 0, 1, 0));
          digitalWrite(2,LOW);
          analogWrite(5,value);
          digitalWrite(4,HIGH);
          analogWrite(6,(d_speed * value));
        }

      } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'Q' == String(G_Bluetooth_value).charAt(1)) {
        Funtion_FLag = false;
        digitalWrite(2,LOW);
        analogWrite(5,0);
        digitalWrite(4,HIGH);
        analogWrite(6,0);
      } else if ('%' == String(G_Bluetooth_value).charAt(0) && '+' == String(G_Bluetooth_value).charAt((G_string_len - 2))) {
        BLE_Change_SPEED = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
        Serial.println(BLE_Change_SPEED);
      } else if ('%' == String(G_Bluetooth_value).charAt(0) && '-' == String(G_Bluetooth_value).charAt((G_string_len - 2))) {
        BLE_Change_SPEED = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
        Serial.println(BLE_Change_SPEED);
      } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'L' == String(G_Bluetooth_value).charAt(1)) {
        digitalWrite(2,LOW);
        analogWrite(5,((BLE_Change_SPEED / 10) * 22.5));
        digitalWrite(4,LOW);
        analogWrite(6,((BLE_Change_SPEED / 10) * 22.5));
      } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'R' == String(G_Bluetooth_value).charAt(1)) {
        digitalWrite(2,HIGH);
        analogWrite(5,((BLE_Change_SPEED / 10) * 22.5));
        digitalWrite(4,HIGH);
        analogWrite(6,((BLE_Change_SPEED / 10) * 22.5));
      } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'S' == String(G_Bluetooth_value).charAt(1)) {
        digitalWrite(2,LOW);
        analogWrite(5,0);
        digitalWrite(4,HIGH);
        analogWrite(6,0);
      } else {
        digitalWrite(2,LOW);
        analogWrite(5,0);
        digitalWrite(4,HIGH);
        analogWrite(6,0);

      }
      G_Bluetooth_value = "";

    }
    G_Bluetooth_value = "";
  }
}

void Light_Seeking() {
  Funtion_FLag = true;
  while (Funtion_FLag) {
    Left_photosensitive = analogRead(A0) / 10;
    Right_photosensitive = analogRead(A3) / 10;
    if (Left_photosensitive > 55 && Right_photosensitive > 55) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    } else {
      if (Left_photosensitive > Right_photosensitive) {
        Lightseeking_Degree = ((float)(Right_photosensitive / Left_photosensitive)) * 90;
        Serial.println("float:");
        Serial.println(((float)(Right_photosensitive / Left_photosensitive)));

      } else if (Left_photosensitive <= Right_photosensitive) {
        Lightseeking_Degree = 180 - ((float)(Left_photosensitive / Right_photosensitive)) * 90;
      }
      if (Lightseeking_Degree <= 90) {
        f = ((float)(Lightseeking_Degree)) / 90;
        digitalWrite(2,HIGH);
        analogWrite(5,speed_value);
        digitalWrite(4,LOW);
        analogWrite(6,(speed_value * f));

      }
      if (Lightseeking_Degree > 90) {
        f = ((float)(180 - Lightseeking_Degree)) / 90;
        digitalWrite(2,HIGH);
        analogWrite(5,(speed_value * f));
        digitalWrite(4,LOW);
        analogWrite(6,speed_value);

      }

    }
    BLE_value = "";
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if ('%' == String(BLE_value).charAt(0) && 'Q' == String(BLE_value).charAt(1)) {
      Funtion_FLag = false;
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
  }
}

void Infraed_Remote() {
  Funtion_FLag = true;
  while (Funtion_FLag) {
    if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_UP) {
      digitalWrite(2,HIGH);
      analogWrite(5,150);
      digitalWrite(4,LOW);
      analogWrite(6,150);

    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_DOWN) {
      digitalWrite(2,LOW);
      analogWrite(5,150);
      digitalWrite(4,HIGH);
      analogWrite(6,150);
    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_LEFT) {
      digitalWrite(2,LOW);
      analogWrite(5,80);
      digitalWrite(4,LOW);
      analogWrite(6,80);
      delay(200);
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_RIGHT) {
      digitalWrite(2,HIGH);
      analogWrite(5,80);
      digitalWrite(4,HIGH);
      analogWrite(6,80);
      delay(200);
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_OK) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_1) {
      digitalWrite(2,LOW);
      analogWrite(5,100);
      digitalWrite(4,LOW);
      analogWrite(6,100);
    } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_3) {
      digitalWrite(2,HIGH);
      analogWrite(5,100);
      digitalWrite(4,HIGH);
      analogWrite(6,100);
    }
    BLE_value = "";
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if ('%' == String(BLE_value).charAt(0) && 'Q' == String(BLE_value).charAt(1)) {
      Funtion_FLag = false;
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
  }
}

void setup(){
  Serial.begin(9600);
  BLE_bit_temp = 'a';
  BLE_value = "";
  G_Bluetooth_value = "";
  G_degree = 0;
  re_string_len = 0;
  IRremote ir(3);

  Left_photosensitive = 0;
  Right_photosensitive = 0;
  Lightseeking_Degree = 0;
  f = 0;
  speed_value = 120;
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  myservo.attach(10);
  Funtion_FLag = false;
  G_string_len = 0;
  BLE_Change_SPEED = 60;
  myservo.write(90);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
}

void loop(){
  while (true) {
    while (Serial.available() > 0) {
      BLE_value = BLE_value + ((char)(Serial.read()));
      delay(2);
    }
    if (0 < String(BLE_value).length()) {
      Serial.println(BLE_value);
      if (128 > String(BLE_value).length()) {
        if ('%' == String(BLE_value).charAt(0) && '#' == String(BLE_value).charAt(2)) {
          switch (String(BLE_value).charAt(1)) {
           case 'G':
            G_Drive();
            break;
           case 'T':
            Infrared_Tracing();
            break;
           case 'P':
            Light_Seeking();
            break;
           case 'I':
            Infraed_Remote();
            break;
           case 'F':
            Ultrasonic_Follow();
            break;
           case 'A':
            Ultrasonic_Avoidance();
            break;
          }
          BLE_value = "";

        } else {
          BLE_value = "";

        }

      }
      BLE_value = "";

    }
  }

}
