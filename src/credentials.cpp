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
  unsigned int offset = block * card::idSize;
  card cardBuffer;

  cardBuffer.block = block;

  for (index = 0; index < card::idSize; index++) {
    unsigned int address = offset + index;

    cardBuffer.id[index] = EEPROM.read(address);
  };

  return cardBuffer;
};

bool Credentials::eraseCard(card &cardBuffer) {
  if (cardBuffer.block == -1) {
    return false;
  };

  unsigned int index;

  for (index = 0; index < card::idSize; index++) {
    cardBuffer.id[index] = 0x00;
  };

  return writeCard(cardBuffer);
};

bool Credentials::writeCard(card &cardBuffer) {
  if (cardBuffer.block == -1) {
    int blankBlock = findBlankBlock();

    if (blankBlock == -1) {
      return false;
    };

    cardBuffer.block = blankBlock;
  };

  unsigned int index;
  unsigned int offset = cardBuffer.block * card::idSize;

  for (index = 0; index < card::idSize; index++) {
    unsigned int address = offset + index;

    EEPROM.update(address, cardBuffer.id[index]);
  };

  return true;
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
