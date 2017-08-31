#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
  private:
    byte baseRed;
    byte baseGreen;
    byte baseBlue;

    byte pinRed;
    byte pinGreen;
    byte pinBlue;

    unsigned int timeBlink;
    unsigned int timePulse;

    unsigned long timeBaseBlink;
    unsigned long timeBasePulse;

    float omega;

  public:
    Led(
      byte pinRed,
      byte pinGreen,
      byte pinBlue,
      unsigned int timeBlink,
      unsigned int timePulse
    );

    void setup(void);
    void loop(void);
    void set(byte valueRed, byte valueGreen, byte valueBlue);
    void blink(byte valueRed, byte valueGreen, byte valueBlue);
    void pulse(byte valueRed, byte valueGreen, byte valueBlue);

  private:
    byte wave(byte baseValue);
};

#endif
