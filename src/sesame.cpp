#include "card-reader.h"
#include "credentials.h"
#include "electric-strike.h"
#include "led.h"
#include "sesame.h"
#include <Arduino.h>

Sesame::Sesame(void) :
  cardReader(pinCardReaderRST, pinCardReaderSS),
  electricStrike(pinElectricStrike),
  led(pinLedRed, pinLedGreen, pinLedBlue, timeLedBlink, timeLedPulse) {
};

void Sesame::loop(void) {
  electricStrike.loop();
  led.loop();

  if (error) {
    return;
  };

  card cardBuffer = cardReader.readCard();

  if (cardBuffer.isBlank()) {
    return;
  };

  if (cardBuffer.isEqualTo(masterCard)) {
    administrating = !administrating;
    led.blink(0, 0, 255);

    return;
  };

  if (credentials.hasCard(cardBuffer)) {
    if (administrating) {
      credentials.eraseCard(cardBuffer);
      led.blink(255, 0, 0);

      return;
    };

    electricStrike.unlock();
    led.blink(0, 255, 0);

    return;
  };

  if (administrating) {
    credentials.writeCard(cardBuffer);
    led.blink(0, 255, 0);

    return;
  };

  led.blink(255, 0, 0);
};

void Sesame::setup(void) {
  cardReader.setup();
  electricStrike.setup();
  led.setup();

  if (!cardReader.isWired()) {
    error = true;

    led.pulse(255, 0, 0);

    return;
  };

  masterCard = credentials.readCard(0);

  if (masterCard.isBlank()) {
    led.set(0, 0, 255);

    do {
      masterCard = cardReader.readCard();

      led.loop();
    } while (masterCard.isBlank());

    led.set(0, 0, 0);

    masterCard.block = 0;
    credentials.writeCard(masterCard);
  };

  led.blink(0, 255, 0);
};
