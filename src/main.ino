#include "built-in-led.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <SPI.h>

constexpr uint8_t relay = 12;

boolean match = false;
boolean programMode = false;
boolean replaceMaster = false;

uint8_t successRead;

byte storedCard[4];
byte readCard[4];
byte masterCard[4];

constexpr uint8_t RST_PIN = 9;
constexpr uint8_t SS_PIN = 10;

MFRC522 mfrc522(SS_PIN, RST_PIN);

boolean checkTwo(byte a[], byte b[]);
boolean findID(byte find[]);
boolean isMaster(byte test[]);
uint8_t findIDSLOT(byte find[]);
uint8_t getID();
void deleteID(byte a[]);
void loop();
void readID(uint8_t number);
void setup();
void writeID(byte a[]);

void setup() {
  digitalWrite(relay, LOW);
  pinMode(relay, OUTPUT);
  builtInLed::setup();

  SPI.begin();

  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);

  if ((v == 0x00) || (v == 0xFF)) {
    while (true) {
      builtInLed::sos();
    }
  }

  if (EEPROM.read(1) != 143) {
    do {
      builtInLed::mc();
      successRead = getID();
    } while (!successRead);

    for (uint8_t j = 0; j < 4; j++) {
      EEPROM.write(2 + j, readCard[j]);
    }

    EEPROM.write(1, 143);
  }

  for (uint8_t i = 0; i < 4; i++) {
    masterCard[i] = EEPROM.read(2 + i);
  }

  builtInLed::ok();
}

void loop() {
  do {
    successRead = getID();
  } while (!successRead);

  if (programMode) {
    if (isMaster(readCard)) {
      programMode = false;
      builtInLed::ok();

      return;
    }

    if (findID(readCard)) {
      deleteID(readCard);
      builtInLed::ok();

      return;
    }

    writeID(readCard);
    builtInLed::ok();

    return;
  }

  if (isMaster(readCard)) {
    programMode = true;
    builtInLed::mc();

    return;
  }

  if (findID(readCard)) {
    digitalWrite(relay, HIGH);
    delay(500);
    digitalWrite(relay, LOW);
    builtInLed::ok();

    return;
  }

  builtInLed::sos();
}

uint8_t getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }

  for (uint8_t i = 0; i < 4; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
  }

  mfrc522.PICC_HaltA();

  return 1;
}

void readID(uint8_t number) {
  uint8_t start = (number * 4 ) + 2;

  for (uint8_t i = 0; i < 4; i++) {
    storedCard[i] = EEPROM.read(start + i);
  }
}

void writeID(byte a[]) {
  uint8_t num = EEPROM.read(0);
  uint8_t start = (num * 4) + 6;
  num++;
  EEPROM.write(0, num);

  for (uint8_t j = 0; j < 4; j++) {
    EEPROM.write(start + j, a[j]);
  }
}

void deleteID(byte a[]) {
  if (!findID(a)) {
    return;
  }

  uint8_t num = EEPROM.read(0);
  uint8_t slot;
  uint8_t start;
  uint8_t looping;
  uint8_t j;
  uint8_t count = EEPROM.read(0);
  slot = findIDSLOT(a);
  start = (slot * 4) + 2;
  looping = ((num - slot) * 4);
  num--;
  EEPROM.write(0, num);

  for (j = 0; j < looping; j++) {
    EEPROM.write( start + j, EEPROM.read(start + 4 + j));
  }

  for (uint8_t k = 0; k < 4; k++) {
    EEPROM.write(start + j + k, 0);
  }
}

boolean checkTwo(byte a[], byte b[]) {
  if ( a[0] != 0 ) {
    match = true;
  }

  for (uint8_t k = 0; k < 4; k++) {
    if (a[k] != b[k]) {
      match = false;

      break;
    }
  }

  if (match) {
    return true;
  }

  return false;
}

uint8_t findIDSLOT(byte find[]) {
  uint8_t count = EEPROM.read(0);

  for (uint8_t i = 1; i <= count; i++) {
    readID(i);

    if (checkTwo(find, storedCard)) {
      return i;
    }
  }
}

boolean findID(byte find[]) {
  uint8_t count = EEPROM.read(0);

  for (uint8_t i = 1; i <= count; i++) {
    readID(i);

    if (checkTwo(find, storedCard)) {
      return true;
    }
  }

  return false;
}

boolean isMaster(byte test[]) {
  if (checkTwo(test, masterCard)) {
    return true;
  }

  return false;
}
