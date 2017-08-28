#include "electric-strike.h"
#include <Arduino.h>

ElectricStrike::ElectricStrike(byte pin) : pin(pin) {
};

void ElectricStrike::setup(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
};

void ElectricStrike::unlock(void) {
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
};
