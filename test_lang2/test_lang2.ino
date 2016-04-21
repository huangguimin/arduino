//#include "SR04.h"
#define TRIG_PIN 3
#define ECHO_PIN 4

//SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
   Serial.begin(115200);
   Serial.println("Example written by Coloz From Arduin.CN");
   inputString.reserve(500);
   delay(1000);
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
