String G_Bluetooth_value;
volatile int G_degree;
volatile int speed_value;
volatile int G_string_len;
volatile int BLE_Change_SPEED;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup(){
  Serial.begin(9600);
  G_Bluetooth_value = "";
  G_degree = 0;
  speed_value = 120;
  G_string_len = 0;
  BLE_Change_SPEED = 60;
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  while (Serial.available() > 0) {
    G_Bluetooth_value = G_Bluetooth_value + ((char)(Serial.read()));
    delay(2);
  }
  if (0 < String(G_Bluetooth_value).length()) {
    Serial.println(G_Bluetooth_value);
    G_string_len = String(G_Bluetooth_value).length();
    Serial.println(G_string_len);
    if (G_string_len <= 7 && ('@' == String(G_Bluetooth_value).charAt(0) && '#' == String(G_Bluetooth_value).charAt((G_string_len - 2)))) {
      G_degree = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
      Serial.println(G_degree);
      float value = (BLE_Change_SPEED / 10) * 16;
      double d_speed = 0.00;
      if (0 <= G_degree && G_degree <= 90) {
        d_speed = (mapfloat(G_degree, 0, 90, 0, 1));
        digitalWrite(2,HIGH);
        analogWrite(5,value);
        digitalWrite(4,LOW);
        analogWrite(6,(d_speed * value));

      } else if (90 < G_degree && G_degree <= 180) {
        d_speed = (mapfloat(G_degree, 180, 90, 0, 1));
        digitalWrite(2,HIGH);
        analogWrite(5,(d_speed * value));
        digitalWrite(4,LOW);
        analogWrite(6,value);
      } else if (-180 < G_degree && G_degree <= -90) {
        d_speed = (mapfloat(G_degree, (-180), (-90), 0, 1));
        digitalWrite(2,LOW);
        analogWrite(5,(d_speed * value));
        digitalWrite(4,HIGH);
        analogWrite(6,value);
      } else if (-90 < G_degree && G_degree < 0) {
        d_speed = (mapfloat(G_degree, (-90), 0, 1, 0));
        digitalWrite(2,LOW);
        analogWrite(5,value);
        digitalWrite(4,HIGH);
        analogWrite(6,(d_speed * value));
      }

    } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'Q' == String(G_Bluetooth_value).charAt(1)) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else if ('%' == String(G_Bluetooth_value).charAt(0) && '+' == String(G_Bluetooth_value).charAt((G_string_len - 2))) {
      BLE_Change_SPEED = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
      Serial.println(BLE_Change_SPEED);
    } else if ('%' == String(G_Bluetooth_value).charAt(0) && '-' == String(G_Bluetooth_value).charAt((G_string_len - 2))) {
      BLE_Change_SPEED = String(String(G_Bluetooth_value).substring(1,(G_string_len - 2))).toInt();
      Serial.println(BLE_Change_SPEED);
    } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'L' == String(G_Bluetooth_value).charAt(1)) {
      digitalWrite(2,LOW);
      analogWrite(5,((BLE_Change_SPEED / 10) * 22.5));
      digitalWrite(4,LOW);
      analogWrite(6,((BLE_Change_SPEED / 10) * 22.5));
    } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'R' == String(G_Bluetooth_value).charAt(1)) {
      digitalWrite(2,HIGH);
      analogWrite(5,((BLE_Change_SPEED / 10) * 22.5));
      digitalWrite(4,HIGH);
      analogWrite(6,((BLE_Change_SPEED / 10) * 22.5));
    } else if ('%' == String(G_Bluetooth_value).charAt(0) && 'S' == String(G_Bluetooth_value).charAt(1)) {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);
    } else {
      digitalWrite(2,LOW);
      analogWrite(5,0);
      digitalWrite(4,HIGH);
      analogWrite(6,0);

    }
    G_Bluetooth_value = "";

  }
  G_Bluetooth_value = "";

}
