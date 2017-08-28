#include "card.h"
#include "credentials.h"
#include <Arduino.h>
#include <EEPROM.h>

bool Credentials::hasCard(card &cardBuffer) {
  unsigned int block;
  unsigned int blocks = EEPROM.length() / card::idSize;

  for (block = 1; block < card::idSize; block++) {
    card cardStored = readCard(block);

    if (cardBuffer.isEqualTo(cardStored)) {
      cardBuffer.block = block;

      return true;
    };
  };

  return false;
};

card Credentials::readCard(unsigned int block) {
  unsigned int index;
  card cardBuffer;

  cardBuffer.block = block;

  for (index = 0; index < card::idSize; index++) {
    unsigned int address = (block * card::idSize) + index;

    cardBuffer.id[index] = EEPROM.read(address);
  };

  return cardBuffer;
};

void Credentials::eraseCard(card &cardBuffer) {
  if (cardBuffer.block == -1) {
    return;
  };

  unsigned int index;

  for (index = 0; index < card::idSize; index++) {
    cardBuffer.id[index] = 0x00;
  };

  writeCard(cardBuffer);
};

void Credentials::writeCard(card &cardBuffer) {
  if (cardBuffer.block == -1) {
    int blankBlock = findBlankBlock();

    if (blankBlock == -1) {
      return;
    }

    cardBuffer.block = blankBlock;
  };

  unsigned int index;

  for (index = 0; index < card::idSize; index++) {
    unsigned int address = (cardBuffer.block * card::idSize) + index;

    EEPROM.update(address, cardBuffer.id[index]);
  };
};

int Credentials::findBlankBlock(void) {
  unsigned int block;
  unsigned int blocks = EEPROM.length() / card::idSize;

  for (block = 1; block < card::idSize; block++) {
    card cardStored = readCard(block);

    if (cardStored.isBlank()) {
      return block;
    };
  };

  return -1;
};
