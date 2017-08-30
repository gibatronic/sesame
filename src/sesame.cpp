#include "built-in-led.h"
#include "credentials.h"
#include "electric-strike.h"
#include "card-reader.h"
#include "sesame.h"
#include <Arduino.h>

Sesame::Sesame(void) : builtInLed(timeBuiltInLed), electricStrike(pinElectricStrike), cardReader(pinCardReaderRST, pinCardReaderSS) {
};

void Sesame::halt(void) {
  while (true) {
    builtInLed.blinkSOS();
  };
};

void Sesame::loop(void) {
  card cardBuffer = cardReader.readCard();

  if (cardBuffer.isEqualTo(masterCard)) {
    administrating = !administrating;

    builtInLed.blinkMC();

    return;
  };

  if (credentials.hasCard(cardBuffer)) {
    if (administrating) {
      credentials.eraseCard(cardBuffer);
    } else {
      electricStrike.unlock();
    };

    builtInLed.blinkOK();

    return;
  };

  if (administrating) {
    credentials.writeCard(cardBuffer);
    builtInLed.blinkOK();

    return;
  };

  builtInLed.blinkSOS();
};

void Sesame::setup(void) {
  builtInLed.setup();
  electricStrike.setup();
  cardReader.setup();

  if (!cardReader.isWired()) {
    halt();

    return;
  };

  masterCard = credentials.readCard(0);

  if (masterCard.isBlank()) {
    builtInLed.blinkMC();

    masterCard = cardReader.readCard();
    masterCard.block = 0;

    credentials.writeCard(masterCard);
  };

  builtInLed.blinkOK();
};
