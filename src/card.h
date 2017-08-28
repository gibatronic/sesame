#ifndef CARD_H
#define CARD_H

#include <Arduino.h>

struct card {
  static constexpr byte idSize = 4;

  byte id[idSize];
  int block = -1;

  bool isBlank(void);
  bool isEqualTo(card cardBuffer);
};

#endif
