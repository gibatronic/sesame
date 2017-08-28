#ifndef ELECTRIC_STRIKE_H
#define ELECTRIC_STRIKE_H

#include <Arduino.h>

class ElectricStrike {
  private:
    byte pin;

  public:
    ElectricStrike(byte pin);
    void setup(void);
    void unlock(void);
};

#endif
