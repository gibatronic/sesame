#include "card.h"
#include <Arduino.h>

bool card::isBlank(void) {
  unsigned int index;

  for (index = 0; index < idSize; index++) {
    if (id[index] != 0x00) {
      return false;
    };
  };

  return true;
};

bool card::isEqualTo(const card &cardBuffer) {
  unsigned int index;

  for (index = 0; index < idSize; index++) {
    if (id[index] != cardBuffer.id[index]) {
      return false;
    };
  };

  return true;
};
