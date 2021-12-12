
#include "midi/midiout.h"

#include "inputs/buttons.h"
#include "inputs/pots.h"
#include "inputs/encoders.h"

#include "outputs/leds.h"

#include "midi/midiin.h"

void setup () {
  Serial.begin(115200); // enable serial communication

  setupPots();
  setupButtons();
  setupEncoders();

  setupLeds();
}

int lastMillis = 0;

void loop () {
  checkMIDI();

  if (millis() >= lastMillis + 10) {
    checkPots();
    checkButtons();
    checkEncoders();

    lastMillis = millis();
  }
}
