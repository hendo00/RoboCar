void setup()
{
  Serial.begin(9600);
  pinMode(7, INPUT);//Left line tracking sensor is connected to the digital IO port D7
  pinMode(8, INPUT);//Center line patrol sensor is connected to the digital IO port D8
  pinMode(9, INPUT);//Right line tracking sensor is connected to the digital IO port D9
}

void loop()
{
  Infrared_Tracing();

}

/*Define a sub-function, 
 the function of this function is to read the output signal 
 of the infrared tracking sensor and print it to the serial monitor*/
void Infrared_Tracing() 
{
  int Left_Tra_Value = 1;
  int Center_Tra_Value = 1;
  int Right_Tra_Value = 1;
  Left_Tra_Value = digitalRead(7);
  Center_Tra_Value = digitalRead(8);
  Right_Tra_Value = digitalRead(9);
  Serial.print("Left Tracking value:");
  Serial.println(Left_Tra_Value);
  Serial.print("Center Tracking value:");
  Serial.println(Center_Tra_Value);
  Serial.print("Right Tracking value:");
  Serial.println(Right_Tra_Value);
  Serial.println("");
  delay(500);
}
