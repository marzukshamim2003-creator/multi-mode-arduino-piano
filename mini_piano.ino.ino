// -------- PIN SETUP --------
const int keyPins[6] = {2, 3, 4, 5, 6, 7};
const int modeButton = 8;
const int buzzerPin = 9;

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 12;

// -------- MODE --------
int currentSet = 0;
bool lastModeState = HIGH;

// -------- TONE SETS --------
int tones[3][6] = {
  {262, 294, 330, 349, 392, 440},  // Set 0
  {523, 587, 659, 698, 784, 880},  // Set 1
  {262, 294, 311, 349, 392, 415}   // Set 2
};

void setup() {

  // Buttons
  for (int i = 0; i < 6; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }

  pinMode(modeButton, INPUT_PULLUP);

  // RGB
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  updateLED();
}

void loop() {

  // ---- MODE SWITCH ----
  bool modeState = digitalRead(modeButton);

  if (modeState == LOW && lastModeState == HIGH) {
    currentSet++;
    if (currentSet > 2) currentSet = 0;
    updateLED();
    delay(200); // simple debounce
  }

  lastModeState = modeState;

  // ---- KEY CHECK ----
  for (int i = 0; i < 6; i++) {
    if (digitalRead(keyPins[i]) == LOW) {
      tone(buzzerPin, tones[currentSet][i]);
      return;
    }
  }

  noTone(buzzerPin);
}

// -------- LED FUNCTION --------
void updateLED() {

  // Turn everything OFF first (HIGH = OFF for common anode)
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);

  if (currentSet == 0) {
    digitalWrite(redPin, LOW);   // Red ON
  }
  else if (currentSet == 1) {
    digitalWrite(greenPin, LOW); // Green ON
  }
  else {
    digitalWrite(bluePin, LOW);  // Blue ON
  }
}
