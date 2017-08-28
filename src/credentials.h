#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include "card.h"
#include <Arduino.h>

class Credentials {
  public:
    bool hasCard(card &cardBuffer);
    card readCard(unsigned int block);
    void eraseCard(card &cardBuffer);
    void writeCard(card &cardBuffer);
  private:
    int findBlankBlock(void);
};

#endif
