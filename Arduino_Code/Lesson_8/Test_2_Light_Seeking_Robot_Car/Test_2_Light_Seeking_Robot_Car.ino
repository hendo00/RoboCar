volatile float Left_photosensitive;
volatile float Right_photosensitive;
volatile int Lightseeking_Degree;
volatile float f;
volatile int speed_value;

void Light_Seeking() {
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
    } else if (Left_photosensitive <= Right_photosensitive) {
      Lightseeking_Degree = 180 - ((float)(Left_photosensitive / Right_photosensitive)) * 90;
    }
    if (Lightseeking_Degree < 90) {
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
    if (Lightseeking_Degree == 90) {
      f = ((float)(Lightseeking_Degree)) / 90;
      digitalWrite(2,HIGH);
      analogWrite(5,speed_value);
      digitalWrite(4,LOW);
      analogWrite(6,speed_value);
    }

  }
}

void setup(){
  Left_photosensitive = 0;
  Right_photosensitive = 0;
  Lightseeking_Degree = 0;
  f = 0;
  speed_value = 120;
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  Light_Seeking();

}
