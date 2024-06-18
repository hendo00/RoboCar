volatile float Left_photosensitive;
volatile float Right_photosensitive;

void Light_Seeking() {
  Left_photosensitive = analogRead(A0);
  Right_photosensitive = analogRead(A3);
  Serial.print("Left_photosensitive:");
  Serial.println(Left_photosensitive);
  Serial.print("Right_photosensitive:");
  Serial.println(Right_photosensitive);
  Serial.println("");
  delay(1000);
}

void setup(){
  Left_photosensitive = 0;
  Right_photosensitive = 0;
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
}

void loop(){
  Light_Seeking();

}
