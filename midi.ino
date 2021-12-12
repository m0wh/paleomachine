
const int BTN_PINS_LENGTH = 2;
// pin, note, channel
const int BTN_PINS[BTN_PINS_LENGTH][3] = {
  {2, 60, 0},
  {3, 62, 0}
};

const int POT_PINS_LENGTH = 2;
// pin, param, channel
const int POT_PINS[POT_PINS_LENGTH][3] = {
  {A0, 20, 0},
  {A1, 21, 0}
};

int btnVals[BTN_PINS_LENGTH];
int btnLastVals[BTN_PINS_LENGTH];

int potVals[POT_PINS_LENGTH];
int potLastVals[POT_PINS_LENGTH];

int incomingByte = 0;

const int PIN_LED_1 = 12;
const int PIN_LED_2 = 13; 

void setup () {
  Serial.begin(115200); // enable serial communication

  for (int i = 0; i < BTN_PINS_LENGTH; i++) {
    pinMode(BTN_PINS[i][0], INPUT_PULLUP);
    btnVals[i] = HIGH;
    btnLastVals[i] = HIGH;
  }

  for (int i = 0; i < POT_PINS_LENGTH; i++) {
    potVals[i] = 0;
    potLastVals[i] = 0;
  }

  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_1, LOW);
  digitalWrite(PIN_LED_2, LOW);
}

const int threshold = 4;
int lastMillis = 0;

void loop () {
  checkMIDI();

  if (millis() >= lastMillis + 2) {
    // POTENTIOMETERS //
    for (int i = 0; i < POT_PINS_LENGTH; i++) {
      potVals[i] = analogRead(POT_PINS[i][0]);

      if (abs(potVals[i] - potLastVals[i]) > threshold) {
        MIDImessage(
          176 + POT_PINS[i][2],
          20 + POT_PINS[i][1],
          map(potVals[i], 0, 1023, 0, 127) // map sensor range to MIDI range
        );

        potLastVals[i] = potVals[i]; // reset old value with new reading
      }
    }

    // BUTTONS //
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

    lastMillis = millis();
  }
}

void checkMIDI(){
  while (Serial.available() >= 3) {
    byte status = Serial.read(); // read first byte
    byte data1 = Serial.read(); // read next byte
    byte data2 = Serial.read(); // read final byte

    for (int channel = 0; channel < 16; channel++) {
      if (status == 144 + channel){ // if note on message
        onNoteOn(channel, data1);
      }

      if (status == 128 + channel){ // if note off message
        onNoteOff(channel, data1);
      }

      if (status == 176 + channel){ // if control change message
        onControlChange(channel, data1, data2);
      }
    }
  }
}

void onNoteOn (int channel, int note) {
  switch (note) {
    case 60: // C3
      digitalWrite(PIN_LED_1, HIGH);
      break;
    case 62: // D3
      digitalWrite(PIN_LED_2, HIGH);
      break;
  }
}

void onNoteOff (int channel, int note) {
  switch (note) {
    case 60: // C3
      digitalWrite(PIN_LED_1, LOW);
      break;
    case 62: // D3
      digitalWrite(PIN_LED_2, LOW);
      break;
  }
}

void onControlChange (int channel, int controller, int value) {
  switch (controller) {
    case 20:
      /* code */
      break;
  }
}

void MIDImessage(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}
