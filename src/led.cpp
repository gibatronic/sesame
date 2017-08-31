#include "led.h"
#include <Arduino.h>

Led::Led(
  byte pinRed,
  byte pinGreen,
  byte pinBlue,
  unsigned int timeBlink,
  unsigned int timePulse) :
  pinRed(pinRed),
  pinGreen(pinGreen),
  pinBlue(pinBlue),
  timeBlink(timeBlink),
  timePulse(timePulse),
  omega(TWO_PI / timePulse) {
};

void Led::setup(void) {
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  set(0, 0, 0);
};

void Led::loop(void) {
  if (timeBaseBlink != 0) {
    if (millis() - timeBaseBlink >= timeBlink) {
      timeBaseBlink = 0;

      set(0, 0, 0);
    };

    return;
  };

  if (timeBasePulse != 0) {
    set(wave(baseRed), wave(baseGreen), wave(baseBlue));

    return;
  };
};

void Led::set(byte valueRed, byte valueGreen, byte valueBlue) {
  analogWrite(pinRed, 255 - valueRed);
  analogWrite(pinGreen, 255 - valueGreen);
  analogWrite(pinBlue, 255 - valueBlue);
};

void Led::blink(byte valueRed, byte valueGreen, byte valueBlue) {
  timeBaseBlink = millis();
  timeBasePulse = 0;

  set(valueRed, valueGreen, valueBlue);
};

void Led::pulse(byte valueRed, byte valueGreen, byte valueBlue) {
  timeBaseBlink = 0;

  if (valueRed == 0 && valueGreen == 0 && valueBlue == 0) {
    timeBasePulse = 0;

    baseRed = 0;
    baseGreen = 0;
    baseBlue = 0;

    set(0, 0, 0);

    return;
  };

  timeBasePulse = millis() - (timePulse / 2);

  baseRed = valueRed;
  baseGreen = valueGreen;
  baseBlue = valueBlue;
};

byte Led::wave(byte baseValue) {
  if (baseValue == 0) {
    return 0;
  };

  float halfBaseValue = baseValue / 2;

  return cos(omega * (millis() - timeBasePulse)) * halfBaseValue + halfBaseValue;
};
