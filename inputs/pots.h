
const int POT_PINS_LENGTH = 2;
// pin, param, channel
const int POT_PINS[POT_PINS_LENGTH][3] = {
  {A0, 20, 0},
  {A1, 21, 0}
};

int potVals[POT_PINS_LENGTH];
int potLastVals[POT_PINS_LENGTH];

const int threshold = 4;

void setupPots () {
  for (int i = 0; i < POT_PINS_LENGTH; i++) {
    potVals[i] = 0;
    potLastVals[i] = 0;
  }
}

int potsLastCheck = 0;

void checkPots () {
  if (millis() >= potsLastCheck + 4) {
    for (int i = 0; i < POT_PINS_LENGTH; i++) {
      potVals[i] = analogRead(POT_PINS[i][0]);

      if (abs(potVals[i] - potLastVals[i]) > threshold) {
        MIDIControlChange(
          POT_PINS[i][2],
          20 + POT_PINS[i][1],
          map(potVals[i], 0, 1023, 0, 127) // map sensor range to MIDI range
        );

        potLastVals[i] = potVals[i]; // reset old value with new reading
      }
    }

    potsLastCheck = millis();
  }
}
