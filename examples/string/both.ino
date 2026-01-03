/**
 * This example uses both STRING and REPORT modes to create a popup
 * in Windows and then close it
 */

#include "HIDKeyboard.h"

void setup() {
  Serial.begin(9600);
  delay(1000); // Wait for serial to initialize

  // GUI R
  // GUI is identical to WIN, just OS-independent
  Keyboard.press(KEY_R, MOD_LEFTGUI);
  delay(100);
  Keyboard.release(KEY_R);
  // A delay is needed when transitioning from REPORT to STRING modes
  delay(1000);

  // STIRNG mshta wbscript:Execute("
  //      CreateObject(""WScript.Shell"")
  //      .Popup(""Hello World!"")(window.close)")
  // Remember to escape quotes inside of a string with a backslash "\"
  Keyboard.write("mshta wbscript:Execute(\"CreateObject(\"\"WScript.Shell\"\").Popup(\"\"Hello World!\"\")(window.close)\")\n");

  // A longer delay is needed when going from STRING to REPORT,
  // since the string buffer needs to clear out
  delay(2000);

  // ALT F4
  Keyboard.press(KEY_F4, MOD_LEFTALT);
  delay(100);
  Keyboard.release(KEY_F4);
}

void loop() {
  // Nothing to do here
}