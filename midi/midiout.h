
void MIDImessage(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void MIDINoteOn(int channel, int note, int velocity = 127) {
  MIDImessage(144 + channel, note, velocity);
}

void MIDINoteOff(int channel, int note) {
  MIDImessage(128 + channel, note, 0);
}

void MIDIControlChange (int channel, int control, int value) {
  MIDImessage(176 + channel, control, value);
}
