
const int ENC_PINS_LENGTH = 2;
// dt, clk, param, channel
const int ENC_PINS[ENC_PINS_LENGTH][4] = {
  {22, 23, 4, 0},
  {24, 25, 5, 0}
};

int encVals[ENC_PINS_LENGTH];
int lastEncVals[ENC_PINS_LENGTH];

void setupEncoders () {
  for (int i = 0; i < ENC_PINS_LENGTH; i++) {
    pinMode(ENC_PINS[i][0], INPUT);
    pinMode(ENC_PINS[i][1], INPUT);

    lastEncVals[i] = digitalRead(ENC_PINS[i][0]);
  }
}

int encodersLastCheck = 0;

void checkEncoders () {
  for (int i = 0; i < ENC_PINS_LENGTH; i++) {
    encVals[i] = digitalRead(ENC_PINS[i][0]);

    if (encVals[i] != lastEncVals[i]) {
      if (millis() - encodersLastCheck > 50 ) {
        if (digitalRead(ENC_PINS[i][1]) != lastEncVals[i]) {
          MIDINoteOff(ENC_PINS[i][3], ENC_PINS[i][2]);
        } else {
          MIDINoteOn(ENC_PINS[i][3], ENC_PINS[i][2]);
        }

        encodersLastCheck = millis();
      }

      lastEncVals[i] = encVals[i];
    }
  }
}
