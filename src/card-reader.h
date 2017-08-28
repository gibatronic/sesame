#ifndef CARD_READER_H
#define CARD_READER_H

#include "card.h"
#include <Arduino.h>
#include <MFRC522.h>

class CardReader {
  private:
    byte pinRST;
    byte pinSS;
    MFRC522 mfrc522;

  public:
    CardReader(byte pinRST, byte pinSS);
    bool isWired(void);
    card readCard(void);
    void setup(void);
};

#endif
