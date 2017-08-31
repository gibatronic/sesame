#include "electric-strike.h"
#include <Arduino.h>

ElectricStrike::ElectricStrike(byte pin) : pin(pin) {
};

void ElectricStrike::setup(void) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
};

void ElectricStrike::loop(void) {
  if (timeBase != 0 && millis() - timeBase >= 500) {
    timeBase = 0;

    digitalWrite(pin, LOW);
  };
};

void ElectricStrike::unlock(void) {
  timeBase = millis();

  digitalWrite(pin, HIGH);
};
