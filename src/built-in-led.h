#ifndef BUILT_IN_LED_H
#define BUILT_IN_LED_H

#include <Arduino.h>

class BuiltInLed {
  private:
    byte time;

  public:
    BuiltInLed(byte time);
    void blinkMC(void);
    void blinkOK(void);
    void blinkSOS(void);
    void setup(void);

  private:
    void dash(void);
    void dot(void);
    void gap(void);
};

#endif
