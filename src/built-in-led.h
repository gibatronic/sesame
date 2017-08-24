#ifndef BUILT_IN_LED_H
#define BUILT_IN_LED_H

#include <Arduino.h>

namespace builtInLed {
  constexpr byte time = 100;

  void dash(void);
  void dot(void);
  void gap(void);
  void mc(void);
  void ok(void);
  void setup(void);
  void sos(void);
}

#endif
