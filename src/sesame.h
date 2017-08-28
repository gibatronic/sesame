#ifndef SESAME_H
#define SESAME_H

#include "built-in-led.h"
#include "card-reader.h"
#include "credentials.h"
#include "electric-strike.h"
#include <Arduino.h>

class Sesame {
  private:
    static constexpr byte pinCardReaderRST = 9;
    static constexpr byte pinCardReaderSS = 10;
    static constexpr byte pinElectricStrike = 12;
    static constexpr byte timeBuiltInLed = 200;

    bool administrating = false;
    card masterCard;

    BuiltInLed builtInLed;
    CardReader cardReader;
    Credentials credentials;
    ElectricStrike electricStrike;

  public:
    Sesame(void);
    void halt(void);
    void loop(void);
    void setup(void);
};

#endif
