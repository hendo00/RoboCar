#include "IR_remote.h"
#include "keymap.h"

IRremote ir(3);

void setup(){
  IRremote ir(3);

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop(){
  if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_UP) {
    digitalWrite(2,HIGH);
    analogWrite(5,150);
    digitalWrite(4,LOW);
    analogWrite(6,150);

  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_DOWN) {
    digitalWrite(2,LOW);
    analogWrite(5,150);
    digitalWrite(4,HIGH);
    analogWrite(6,150);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_LEFT) {
    digitalWrite(2,LOW);
    analogWrite(5,50);
    digitalWrite(4,LOW);
    analogWrite(6,50);
    delay(200);
    digitalWrite(2,LOW);
    analogWrite(5,0);
    digitalWrite(4,HIGH);
    analogWrite(6,0);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_RIGHT) {
    digitalWrite(2,HIGH);
    analogWrite(5,50);
    digitalWrite(4,HIGH);
    analogWrite(6,50);
    delay(200);
    digitalWrite(2,LOW);
    analogWrite(5,0);
    digitalWrite(4,HIGH);
    analogWrite(6,0);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_OK) {
    digitalWrite(2,LOW);
    analogWrite(5,0);
    digitalWrite(4,HIGH);
    analogWrite(6,0);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_1) {
    digitalWrite(2,LOW);
    analogWrite(5,130);
    digitalWrite(4,LOW);
    analogWrite(6,130);
  } else if (ir.getIrKey(ir.getCode(),1) == IR_KEYCODE_3) {
    digitalWrite(2,HIGH);
    analogWrite(5,130);
    digitalWrite(4,HIGH);
    analogWrite(6,130);
  }

}
