#ifndef SESAME_H
#define SESAME_H

#include "card-reader.h"
#include "credentials.h"
#include "electric-strike.h"
#include "led.h"
#include <Arduino.h>

class Sesame {
  private:
    static constexpr byte pinCardReaderRST = 9;
    static constexpr byte pinCardReaderSS = 10;

    static constexpr byte pinElectricStrike = 12;

    static constexpr byte pinLedRed = 3;
    static constexpr byte pinLedGreen = 5;
    static constexpr byte pinLedBlue = 6;

    static constexpr unsigned int timeLedBlink = 400;
    static constexpr unsigned int timeLedPulse = 1000;

    bool administrating = false;
    bool error = false;

    card masterCard;

    CardReader cardReader;
    Credentials credentials;
    ElectricStrike electricStrike;
    Led led;

  public:
    Sesame(void);
    void halt(void);
    void loop(void);
    void setup(void);
};

#endif
