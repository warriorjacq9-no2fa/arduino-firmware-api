/**
 * This example executes a set of keystrokes, holding some
 * keys down while others are pressed.
 * It uses the firmware's REPORT mode, which allows to press many keys
 * simultaneously
 *
 * In this program, it opens Task Manager
 */

#include "HIDKeyboard.h"

void setup() {
  Serial.begin(9600);
  delay(1000); // Wait for serial to initialize

  // CTRL SHIFT ESC
  Keyboard.press(KEY_ESC, MOD_RIGHTCTRL | MOD_RIGHTSHIFT);
  delay(100);
  Keyboard.release(KEY_ESC);
}

void loop() {
  // Nothing to do here
}