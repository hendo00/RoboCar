void setup(){
  pinMode(2, OUTPUT);//
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  digitalWrite(2,HIGH);
  analogWrite(5,50);
  digitalWrite(4,LOW);
  analogWrite(6,50);
  delay(2000);
  digitalWrite(2,LOW);
  analogWrite(5,50);
  digitalWrite(4,HIGH);
  analogWrite(6,50);
  delay(2000);
  digitalWrite(2,LOW);
  analogWrite(5,50);
  digitalWrite(4,LOW);
  analogWrite(6,50);
  delay(2000);
  digitalWrite(2,HIGH);
  analogWrite(5,50);
  digitalWrite(4,HIGH);
  analogWrite(6,50);
  delay(2000);

}
