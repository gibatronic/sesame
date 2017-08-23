#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>

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

void setup() {
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  Serial.begin(9600);
  SPI.begin();

  mfrc522.PCD_Init();
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  Serial.println(F("SESAME"));
  Serial.println("");

  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);

  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("Communication with MFRC522 has failed."));

    while(true);
  }

  if (EEPROM.read(1) != 143) {
    Serial.println(F("Define a master card by scanning one now."));

    do {
      successRead = getID();
    } while (!successRead);

    for (uint8_t j = 0; j < 4; j++) {
      EEPROM.write(2 + j, readCard[j]);
    }

    EEPROM.write(1, 143);

    Serial.println(F("Succesfully defined the master card."));
    Serial.println("");
  }

  for (uint8_t i = 0; i < 4; i++) {
    masterCard[i] = EEPROM.read(2 + i);
  }

  Serial.println(F("Ready to bounce!"));
  Serial.println("");
}

void loop() {
  do {
    successRead = getID();
  } while (!successRead);

  if (programMode) {
    if (isMaster(readCard)) {
      programMode = false;

      Serial.println(F("Master card scanned."));
      Serial.println(F("Exiting program mode."));
      Serial.println("");
    } else {
      if (findID(readCard)) {
        Serial.println(F("I know this PICC, removing..."));
        deleteID(readCard);
        Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));

        return;
      }

      Serial.println(F("I do not know this PICC, adding..."));
      writeID(readCard);
      Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));
    }
  } else {
    if (isMaster(readCard)) {
      programMode = true;
      Serial.println(F("Hello Master - Entered Program Mode"));
      uint8_t count = EEPROM.read(0);
      Serial.print(F("I have "));
      Serial.print(count);
      Serial.print(F(" record(s) on EEPROM"));
      Serial.println("");
      Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));
      Serial.println(F("Scan Master Card again to Exit Program Mode"));

      return;
    }

    if (findID(readCard)) {
      Serial.println(F("Welcome! Open sesame!"));
      granted();
      return;
    }

    Serial.println(F("You shall not pass"));
    denied();
  }
}

void granted() {
  digitalWrite(relay, HIGH);
  delay(500);
  digitalWrite(relay, LOW);
  delay(1000);
}

void denied() {
  delay(1000);
}

uint8_t getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }

  Serial.println(F("Scanned PICC's UID:"));

  for (uint8_t i = 0; i < 4; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }

  Serial.println("");
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
  if (findID(a)) {
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));

    return;
  }

  uint8_t num = EEPROM.read(0);
  uint8_t start = (num * 4) + 6;
  num++;
  EEPROM.write(0, num);

  for (uint8_t j = 0; j < 4; j++) {
    EEPROM.write(start + j, a[j]);
  }

  Serial.println(F("Succesfully added ID record to EEPROM"));
}

void deleteID(byte a[]) {
  if (!findID(a)) {
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));

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

  Serial.println(F("Succesfully removed ID record from EEPROM"));
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
