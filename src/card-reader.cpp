#include "card-reader.h"
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

CardReader::CardReader(byte pinRST, byte pinSS) : pinRST(pinRST), pinSS(pinSS), mfrc522(pinSS, pinRST) {
};

bool CardReader::isWired(void) {
  byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);

  if (version == 0x00 || version == 0xFF) {
    return false;
  };

  return true;
};

card CardReader::readCard(void) {
  bool read = false;
  card cardBuffer;
  unsigned int index;

  do {
    if (!mfrc522.PICC_IsNewCardPresent()) {
      continue;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      continue;
    }

    for (index = 0; index < card::idSize; index++) {
      cardBuffer.id[index] = mfrc522.uid.uidByte[index];
    }

    read = true;
    mfrc522.PICC_HaltA();
  } while (!read);

  return cardBuffer;
};

void CardReader::setup(void) {
  SPI.begin();

  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
};
