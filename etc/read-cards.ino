#include <Arduino.h>
#include <EEPROM.h>

void loop();
void setup();

void loop() {
};

void setup() {
  unsigned int block;
  unsigned int blocks;
  unsigned int idSize;

  idSize = 4;
  blocks = EEPROM.length() / idSize;

  Serial.begin(9600);
  while (!Serial);

  Serial.println("B0 B1 B2 B3 #BLOCK");

  for (block = 0; block < blocks; block++) {
    unsigned int index;

    for (index = 0; index < idSize; index++) {
      unsigned int address = (block * idSize) + index;
      byte byte = EEPROM.read(address);

      if (byte < 10) {
        Serial.print("0");
      }

      Serial.print(byte, HEX);

      if (index != idSize - 1) {
        Serial.print(" ");
      }
    }

    Serial.print(" #");
    Serial.print(block);
    Serial.println("");
  };

  Serial.end();
};
