/*
  Pin Tester

  Reads all pins as defined in dPins[] and aPins[] below. It scans
  for changes on the digital pins registers the last one who had
  any change. It also scans and values of the defined analog pins.
  The results are output over serial and can be monitored in the
  Serial Monitor.

  Change dPins[] and aPins[] as necessary to reflect your Arduino
  board and your needs. By default the code below is set up to
  work with an Arduino Pro Micro.

  Do not use digital pins 0 and 1 as they are used for serial
  communication.

  Created by Daniel Jansson
  http://www.youtube.com/switchandlever

  This code is in the public domain.

*/

// Define which digital pins to test
const uint8_t dPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16};

// Define which analog pins to test
const uint8_t aPins[] = {A0, A1, A2, A3 };

// Arrays to store values
int dVals[sizeof(dPins)];
int dValsOld[sizeof(dPins)];

String lastPin = "No pin!";

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait until serial port is open

  // enable digital pins
  for (int i = 0; i < (sizeof(dPins)); i++) {
    pinMode(dPins[i], INPUT_PULLUP);
    dVals[i] = digitalRead(i);
  }

  // enable analog pins
  for (int j = 0; j < (sizeof(aPins)); j++) {
    pinMode(aPins[j], INPUT_PULLUP);
  }

}

void loop() {

  // Copy array for comparison
  for (int v = 0 ; v < sizeof(dPins); ++v ) {
    dValsOld[v] = dVals[v];
  }

  // Read pins and store their state in array
  for (int i = 0; i < sizeof(dPins); i++) {
    dVals[i] = digitalRead(dPins[i]);
  }

  // Compare old and new arrays to find last pin
  for (int p = 0; p < sizeof(dPins); p++) {
    if (dValsOld[p] != dVals[p] && dVals[p] == 0) {
      lastPin = "D" + String(dPins[p]);
      Serial.print("New pin:  ");
      Serial.print(lastPin);
      delay(1000);
    }
  }

  // Output to serial monitor
  Serial.print("Last pin: ");
  Serial.print(lastPin);
  Serial.print("\t\t");
  Serial.print("Analog values:");

  // Output analog data
  for (int a = 0; a < sizeof(aPins); a++) {
    Serial.print("  A");
    Serial.print(a);
    Serial.print(" = ");
    Serial.print(analogRead(aPins[a]));
  }

  Serial.println("  ");

}
