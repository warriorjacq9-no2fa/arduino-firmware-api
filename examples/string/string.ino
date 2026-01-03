/**
 * This example types a string on the keyboard, using the firmware's
 * STRING mode.
 */

#include "HIDKeyboard.h"

void setup() {
  Serial.begin(9600);
  delay(1000); // Wait for serial to initialize
  Keyboard.write("Hello, world!");
}

void loop() {
  // Nothing to do here
}