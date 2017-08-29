#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include "card.h"
#include <Arduino.h>

class Credentials {
  public:
    bool hasCard(card &cardBuffer);
    card readCard(unsigned int block);
    bool eraseCard(card &cardBuffer);
    bool writeCard(card &cardBuffer);
  private:
    int findBlankBlock(void);
};

#endif
