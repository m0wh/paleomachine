
#include "midi/midiout.h"

#include "outputs/leds.h"
#include "outputs/matrix.h"

#include "inputs/buttons.h"
#include "inputs/pots.h"
#include "inputs/encoders.h"

#include "midi/midiin.h"

void setup () {
  Serial.begin(115200); // enable serial communication

  setupPots();
  setupButtons();
  setupEncoders();

  setupLeds();
  setupMatrix();
}

void loop () {
  checkMIDI();
  checkPots();
  checkButtons();
  checkEncoders();
  loopMatrix();
}
