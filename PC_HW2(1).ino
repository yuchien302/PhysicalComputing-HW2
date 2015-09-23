/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int morse[5] = {0,0,0,0,0};
int location = 0;
int highCount = 0;
int number = 0;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (location == 5) {
    Serial.println(number);
    location++;
  }
  else if (location < 5) {
      if (buttonState == HIGH) {
      highCount++;
      // turn LED on:
      digitalWrite(ledPin, HIGH);
    }
    else {
      if (highCount > 0 && highCount <= 10) {
        morse[location++] = 0;
      }
      else if (highCount > 10) {
        morse[location++] = 1;
      }
      highCount = 0;
      // turn LED off:
      digitalWrite(ledPin, LOW);
    }
  }

  void morseToNumber() {
    int total = 0;
    for (int i = 0; i < 5; ++i) {
      total += morse[i];
    }

    if (morse[0] == 0) {
      number = 5 - total;
    }
    else
    {
      number = (5 + total) % 10;
    }
  }
}


