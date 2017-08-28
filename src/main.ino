#include "sesame.h"
#include <Arduino.h>

Sesame sesame;

void loop(void);
void setup(void);

void loop(void) {
  sesame.loop();
};

void setup(void) {
  sesame.setup();
};
