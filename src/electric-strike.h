#ifndef ELECTRIC_STRIKE_H
#define ELECTRIC_STRIKE_H

#include <Arduino.h>

class ElectricStrike {
  private:
    byte pin;
    unsigned int timeOpen;
    unsigned long timeBase;

  public:
    ElectricStrike(
      byte pin,
      unsigned int timeOpen
    );

    void setup(void);
    void loop(void);
    void unlock(void);
};

#endif
