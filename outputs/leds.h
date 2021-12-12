
const int PIN_LED_1 = 12;
const int PIN_LED_2 = 13; 

void setupLeds () {
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  digitalWrite(PIN_LED_1, LOW);
  digitalWrite(PIN_LED_2, LOW);
}
