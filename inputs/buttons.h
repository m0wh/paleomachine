
const int BTN_PINS_LENGTH = 4;
// pin, note, channel
const int BTN_PINS[BTN_PINS_LENGTH][3] = {
  {2, 0, 0}, // btn 1
  {3, 1, 0}, // btn 2
  {4, 2, 0}, // enc 1
  {5, 3, 0}, // enc 2
};

int btnVals[BTN_PINS_LENGTH];
int btnLastVals[BTN_PINS_LENGTH];

void setupButtons () {
  for (int i = 0; i < BTN_PINS_LENGTH; i++) {
    pinMode(BTN_PINS[i][0], INPUT_PULLUP);
    btnVals[i] = HIGH;
    btnLastVals[i] = HIGH;
  }
}

int buttonsLastCheck = 0;

void checkButtons () {
  if (millis() >= buttonsLastCheck + 4) {
    for (int i = 0; i < BTN_PINS_LENGTH; i++) {
      btnVals[i] = digitalRead(BTN_PINS[i][0]);

      if (btnVals[i] != btnLastVals[i]) {
        if (btnVals[i] == LOW) { // note on
          MIDImessage(144 + BTN_PINS[i][2], BTN_PINS[i][1], 127);
          btnLastVals[i] = btnVals[i];
        } else { // note off
          MIDImessage(128 + BTN_PINS[i][2], BTN_PINS[i][1], 0);
          btnLastVals[i] = btnVals[i];
        }
      }
    }

    buttonsLastCheck = millis();
  }
}
