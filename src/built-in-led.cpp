#include "built-in-led.h"
#include <Arduino.h>

BuiltInLed::BuiltInLed(byte time) : time(time) {
};

void BuiltInLed::blinkMC(void) {
  dash(); dash();
  dash(); dot(); dash(); dot();
  gap();
};

void BuiltInLed::blinkOK(void) {
  dash(); dash(); dash();
  dash(); dot(); dash();
  gap();
};

void BuiltInLed::blinkSOS(void) {
  dot(); dot(); dot();
  dash(); dash(); dash();
  dot(); dot(); dot();
  gap();
};

void BuiltInLed::dash(void) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time * 3);
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
};

void BuiltInLed::dot(void) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
};

void BuiltInLed::gap(void) {
  delay(time * 7);
};

void BuiltInLed::setup(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
};
