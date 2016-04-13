#include "SR04.h"
#define TRIG_PIN 3
#define ECHO_PIN 4

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
byte a;

void setup() {
   Serial.begin(38400);
   Serial.println("Example written by Coloz From Arduin.CN");
   delay(1000);
}

void loop() {
   a=sr04.Distance();
   Serial.write(a);
   //Serial.println("cm");
   //Serial.println(" ");
   //delay(1);
}
