
#include <Servo.h>

volatile int D_mix;
volatile int D_mid;
volatile int D_max;
volatile int Front_Distance;
volatile int Left_Distance;
volatile int Right_Distance;
volatile int Right_IR_Value;
volatile int Left_IR_Value;

void Ultrasonic_obstacle_avoidance() {
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
    Detect_Left_and_Right__distance();
    if ((D_mix < Left_Distance && Left_Distance < D_max) && (D_mix < Right_Distance && Right_Distance < D_max)) {
      if (Right_Distance > Left_Distance) {
        digitalWrite(2,HIGH);
        analogWrite(5,(9 * 22.5));
        digitalWrite(4,HIGH);
        analogWrite(6,(9 * 22.5));
        delay(300);

      } else {
        digitalWrite(2,LOW);
        analogWrite(5,(9 * 22.5));
        digitalWrite(4,LOW);
        analogWrite(6,(9 * 22.5));
        delay(300);

      }

    } else if (D_mix < Left_Distance && Left_Distance < D_max || D_mix < Right_Distance && Right_Distance < D_max) {
      if (D_mix < Left_Distance && Left_Distance < D_max) {
        digitalWrite(2,LOW);
        analogWrite(5,(7 * 22.5));
        digitalWrite(4,LOW);
        analogWrite(6,(7 * 22.5));
        delay(310);

      } else if (D_mix < Right_Distance && Right_Distance < D_max) {
        digitalWrite(2,HIGH);
        analogWrite(5,(7 * 22.5));
        digitalWrite(4,HIGH);
        analogWrite(6,(7 * 22.5));
        delay(310);
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
}

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

void Detect_Left_and_Right__distance() {
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
}

void Obstacle_Avoidance_Main() {
  Left_IR_Value = digitalRead(A1);
  Right_IR_Value = digitalRead(A2);
  Front_Distance = checkdistance();
  Serial.println(Front_Distance);
  Infrared_Obstacle_Avoidance();
  Ultrasonic_obstacle_avoidance();
}

void Infrared_Obstacle_Avoidance() {
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
}

void setup(){
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  myservo.attach(10);
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  D_mix = 5;
  D_mid = 10;
  D_max = 400;
  Front_Distance = 0;
  Left_Distance = 0;
  Right_Distance = 0;
  Right_IR_Value = 1;
  Left_IR_Value = 1;
  myservo.write(90);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop(){
  Obstacle_Avoidance_Main();

}
