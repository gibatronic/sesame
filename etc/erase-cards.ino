#include <Arduino.h>
#include <EEPROM.h>

void loop();
void setup();

void loop() {
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  unsigned int index;
  unsigned int length = EEPROM.length();

  for (index = 0; index < length; index++) {
    EEPROM.update(index, 0);
  };

  digitalWrite(LED_BUILTIN, HIGH);
};
