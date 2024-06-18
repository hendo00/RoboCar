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
void Ultrasonic_Sensor_Module() {
  int Distance = 0;
  Distance = checkdistance();
  Serial.print("Distance:");
  Serial.print(Distance);
  Serial.println("CM");
  delay(100);
}
void setup(){
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
}
void loop(){
  Ultrasonic_Sensor_Module();

}
