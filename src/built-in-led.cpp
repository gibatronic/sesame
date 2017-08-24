#include "built-in-led.h"
#include <Arduino.h>

namespace builtInLed {
  void dash(void) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(time * 3);
    digitalWrite(LED_BUILTIN, LOW);
    delay(time);
  }

  void dot(void) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(time);
    digitalWrite(LED_BUILTIN, LOW);
    delay(time);
  }

  void gap(void) {
    delay(time * 7);
  }

  void mc(void) {
    dash(); dash();
    dash(); dot(); dash(); dot();
    gap();
  }

  void ok(void) {
    dash(); dash(); dash();
    dash(); dot(); dash();
    gap();
  }

  void setup(void) {
    pinMode(LED_BUILTIN, OUTPUT);
  }

  void sos(void) {
    dot(); dot(); dot();
    dash(); dash(); dash();
    dot(); dot(); dot();
    gap();
  }
}
