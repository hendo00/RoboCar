String BLE_value;

void setup(){
  Serial.begin(9600);
  BLE_value = "";
}

void loop(){
  // If the serial port has received new information, it will not stop until the new data is received.
  while (Serial.available() > 0) {
    // Combine the ending characters into a string
    BLE_value = BLE_value + ((char)(Serial.read()));
    // Need to delay waiting for the reception to complete
    delay(2);
  }
  if (0 < String(BLE_value).length()) {
    // Print the received string to the serial monitor
    Serial.println(BLE_value);
    BLE_value = "";

  }

}
