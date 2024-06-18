
#include <Servo.h>

Servo myservo;

void setup(){
  myservo.attach(10);
  // Set initial angle of servo to 90°
  myservo.write(90);
}

void loop(){
  // Set angle of servo to 15°
  myservo.write(15);
  delay(2000);
  myservo.write(168);
  delay(2000);
  myservo.write(90);
  delay(2000);

}
