/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */

String inputString = "";         // a string to hold incoming data
String outputString = "";
String CMD_String = "";
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial1.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  outputString.reserve(200); 
  CMD_String.reserve(100);
  delay(5000);
    Serial.println("heloA4");
  Serial.println("heloA5");
}
byte state = 0;
int i=1;
void loop() {
    switch(state)
    { 
        case 0:
          Serial1.println("AT+CWJAP=\"jinda5\",\"jinda54312\"\r");
          state = 1;
          break; 
        case 2:
          Serial1.println("AT+CIFSR\r");
          state = 3;
          break;
        case 4:
          Serial1.println("AT+CIPSTART=\"TCP\",\"tcp.lewei50.com\",9960\r");
          state = 5;
          break;
        case 6:
          Serial1.println("AT+CIPMODE=1\r");
          state = 7;
          break;
        case 8:
          Serial1.println("AT+CIPSEND\r");
          state = 9;
          break;
        case 10:
          Serial1.println("{\"method\":\"update\",\"gatewayNo\": \"01\",\"userkey\":\"85be7b17d02346e981d5d4a48e3d8453\"}&^!");
          delay(500);
          state = 12;
          break;
        case 12:
          CMD_String = "{\"method\":\"upload\",\"data\":[{\"Name\":\"T1\",\"Value\":\"";
          CMD_String += i;
          CMD_String += "\"}]}&^!";
          Serial1.println(CMD_String);
          CMD_String = "";
          delay(11000);
          if(i++>=255)i=0;
          //state = 7;valueOf
          break;
        default:
          break;
    }
}

void serialEvent1() {
  while (Serial1.available()) {
     char outChar = (char)Serial1.read();
     outputString += outChar;
    if (outChar == '\n') {
      Serial.println(outputString);
      if(outputString == "OK\r\n")
        state++;
      outputString = "";
    }
    else if(outChar == '!')
    {
      Serial.println(outputString);
      if(outputString == "{\"method\":\"send\",\"gatewayNo\":\"01\",\"userkey\":\"85be7b17d02346e981d5d4a48e3d8453\",\"f\":\"getAllSensors\"}&^!")
      {Serial.println("ctrul");}
      outputString = "";
    }
  }
}
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\r') {
        //inputString += "AT\r\n";
        Serial1.println(inputString);
    // clear the string:
        inputString = "";
    }
  }
}


