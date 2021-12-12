
int incomingByte = 0;

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
