
#include <Servo.h>

volatile int D_mix;
volatile int D_mid;
volatile int D_max;

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

void Ultrasonic_Follow() {
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
}

void setup(){
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Serial.begin(9600);
  myservo.attach(10);
  myservo.write(90);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  Ultrasonic_Follow();

}
