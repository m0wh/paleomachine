
#include <LedControl.h>

const int DIN = 51; // Data IN (MOSI)
const int CS = 53; // Chip Select (SS)
const int CLK = 52; // Clock (SCK)

LedControl lc = LedControl(DIN, CLK, CS, 2); // Pins: DIN,CLK,CS, # of Display connected

void setupMatrix () {
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.setIntensity(0, 10);
  lc.setIntensity(1, 10);
  lc.clearDisplay(0);
  lc.clearDisplay(1);
}

int matrixLastCheck = 0;
void loopMatrix () {
  if (millis() >= matrixLastCheck + 10000) {
    for(int i = 0; i < 8; i++) {
      for(int j = 0; j < 8; j++) {
        lc.setLed(0, i, j, random(100) > 80);
        lc.setLed(1, i, j, random(100) > 80);
      }
    }

    matrixLastCheck = millis();
  }
}
