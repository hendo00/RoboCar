void Ultrasonic_Avoidance() {
  int Right_IR_Value = 1;
  int Left_IR_Value = 1;
  Left_IR_Value = digitalRead(A1);
  Right_IR_Value = digitalRead(A2);
  Serial.print("Left_IR_Value:");
  Serial.println(Left_IR_Value);
  Serial.print("Right_IR_Value:");
  Serial.println(Right_IR_Value);
  Serial.println("");
  delay(1000);
}

void setup(){
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop(){
  Ultrasonic_Avoidance();

}
