#include "IR_remote.h"
#include "keymap.h"

IRremote ir(12);

#include <Servo.h>

String BT_value;
String BT_value_temp;
volatile boolean Funtion_FLag;
volatile int Left_Tra_Value;
volatile int Center_Tra_Value;
volatile int Right_Tra_Value;
volatile int Black;
volatile int white;
volatile int Front_Distance;
volatile int Left_Distance;
volatile int Right_Distance;
volatile char IR_Car_Mode;
volatile boolean IR_Mode_Flag;
Servo servo_A2;

void Infrared_Tracing() {
  Left_Tra_Value = digitalRead(9);
  Center_Tra_Value = digitalRead(10);
  Right_Tra_Value = digitalRead(11);
  if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {
    Move_Forward(130);

  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value != Black)) {
    Rotate_Left(180);
  } else if (Left_Tra_Value == Black && (Center_Tra_Value != Black && Right_Tra_Value != Black)) {
    Rotate_Left(160);
  } else if (Left_Tra_Value != Black && (Center_Tra_Value != Black && Right_Tra_Value == Black)) {
    Rotate_Right(160);
  } else if (Left_Tra_Value != Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {
    Rotate_Right(180);
  } else if (Left_Tra_Value == Black && (Center_Tra_Value == Black && Right_Tra_Value == Black)) {
    STOP();
  }
}

void Move_Forward(int car_speed) {
  digitalWrite(2,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void Move_Backward(int car_speed) {
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void Rotate_Left(int car_speed) {
  digitalWrite(2,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void Rotate_Right(int car_speed) {
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,HIGH);
  analogWrite(5,car_speed);
  analogWrite(6,car_speed);
}

void STOP() {
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  analogWrite(5,0);
  analogWrite(6,0);
}

float checkdistance() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
  delay(10);
  return distance;
}

void Ultrasonic_Avoidance() {
  Front_Distance = checkdistance();
  if (0 < Front_Distance && Front_Distance <= 20) {
    STOP();
    delay(100);
    servo_A2.write(180);
    delay(500);
    Left_Distance = checkdistance();
    delay(100);
    servo_A2.write(0);
    delay(500);
    Right_Distance = checkdistance();
    delay(100);
    if (Right_Distance <= Left_Distance) {
      Rotate_Left(255);
      servo_A2.write(90);
      delay(300);

    } else {
      Rotate_Right(255);
      servo_A2.write(90);
      delay(300);

    }

  } else {
    Move_Forward(150);

  }
}

void IR_remote_control() {
  switch (IR_Car_Mode) {
   case 'b':
    Move_Backward(255);
    delay(300);
    STOP();
    IR_Car_Mode = ' ';
    break;
   case 'f':
    Move_Forward(255);
    delay(300);
    STOP();
    IR_Car_Mode = ' ';
    break;
   case 'l':
    Rotate_Left(255);
    delay(300);
    STOP();
    IR_Car_Mode = ' ';
    break;
   case 'r':
    Rotate_Right(255);
    delay(300);
    STOP();
    IR_Car_Mode = ' ';
    break;
   case 's':
    STOP();
    IR_Car_Mode = ' ';
    break;
  }
  if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_UP) {
    IR_Car_Mode = 'f';
    IR_Mode_Flag = true;

  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_LEFT) {
    IR_Car_Mode = 'l';
    IR_Mode_Flag = true;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_DOWN) {
    IR_Car_Mode = 'b';
    IR_Mode_Flag = true;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_RIGHT) {
    IR_Car_Mode = 'r';
    IR_Mode_Flag = true;
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_OK) {
    IR_Car_Mode = 's';
    IR_Mode_Flag = true;
  }
}

void setup(){
  Serial.begin(9600);
  BT_value = "";
  BT_value_temp = "";
  Funtion_FLag = false;
  Left_Tra_Value = 1;
  Center_Tra_Value = 1;
  Right_Tra_Value = 1;
  Black = 1;
  white = 0;
  Front_Distance = 0;
  Left_Distance = 0;
  Right_Distance = 0;
  IR_Car_Mode = ' ';
  IR_Mode_Flag = false;
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  servo_A2.attach(A2);
}

void loop(){
  while (true) {
    while (Serial.available() > 0) {
      BT_value_temp = BT_value_temp + ((char)(Serial.read()));
      delay(2);
      if (!Serial.available() > 0) {
        BT_value = BT_value_temp;
        BT_value_temp = "";

      }
    }
    if (0 < String(BT_value).length()) {
      Serial.println(BT_value);
      Serial.println(String(BT_value).length());
      if (4 >= String(BT_value).length()) {
        if ('%' == String(BT_value).charAt(0) && '#' == String(BT_value).charAt((String(BT_value).length() - 1))) {
          if (IR_Mode_Flag == true) {
            STOP();
            IR_Car_Mode = ' ';
            IR_Mode_Flag = false;

          }
          switch (String(BT_value).charAt(1)) {
            case 'F':
            Move_Forward(255);
            delay(500);
            BT_value = "";
            break;
           case 'B':
            Move_Backward(255);
            delay(500);
            BT_value = "";
            break;
           case 'L':
            Rotate_Left(230);
            delay(300);
            BT_value = "";
            break;
           case 'R':
            Rotate_Right(230);
            delay(300);
            BT_value = "";
            break;
           case 'T':
            Infrared_Tracing();
            break;
           case 'S':
            BT_value = "";
            STOP();
            break;
           case 'A':
            Ultrasonic_Avoidance();
            break;
           case 'Z':
            break;
          }

        }

      } else {
        BT_value = "";
        STOP();

      }

    } else {
      STOP();

    }
    IR_remote_control();
  }

}
