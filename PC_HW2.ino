
// set pin numbers:
const int buttonPin = 2;
const int strobePin = 3;
const int dataPin = 4;
const int cpPin = 5;
const int oePin = 6;

const int c0Pin = 8;
const int c1Pin = 9;
const int c2Pin = 10;
const int c3Pin = 11;
const int c4Pin = 12;

const int ledPin =  13;

// global state:
int buttonState = 0;
int row_idx = 0;

int morse[5] = {0,0,0,0,0};
int location = 0;
int highCount = 0;
int digit = 11;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  pinMode(c0Pin, OUTPUT);
  pinMode(c1Pin, OUTPUT);
  pinMode(c2Pin, OUTPUT);
  pinMode(c3Pin, OUTPUT);
  pinMode(c4Pin, OUTPUT);

  pinMode(strobePin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(cpPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  
  Serial.begin(9600);
  
  digitalWrite(c0Pin, LOW);
  digitalWrite(c1Pin, LOW);
  digitalWrite(c2Pin, LOW);
  digitalWrite(c3Pin, LOW);
  digitalWrite(c4Pin, LOW);
  
  digitalWrite(strobePin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(cpPin, HIGH);
  digitalWrite(oePin, HIGH);
}

int digits[12][7][5] = {{{0,0,0,0,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0}},
                         
                        {{1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0}},

                        {{0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {0,0,0,0,0},
                         {0,1,1,1,1},
                         {0,1,1,1,1},
                         {0,0,0,0,0}},

                        {{0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {0,0,0,0,0}},

                        {{0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0}},

                        {{0,0,0,0,0},
                         {0,1,1,1,1},
                         {0,1,1,1,1},
                         {0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {0,0,0,0,0}},

                        {{0,0,0,0,0},
                         {0,1,1,1,1},
                         {0,1,1,1,1},
                         {0,0,0,0,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0}},

                        {{0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0}},

                        {{0,0,0,0,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0}},

                        {{0,0,0,0,0},
                         {0,1,1,1,0},
                         {0,1,1,1,0},
                         {0,0,0,0,0},
                         {1,1,1,1,0},
                         {1,1,1,1,0},
                         {0,0,0,0,0}},
                         
                        {{0,1,1,1,0},
                         {0,0,1,0,0},
                         {1,0,0,0,1},
                         {1,1,0,1,1},
                         {1,0,0,0,1},
                         {0,0,1,0,0},
                         {0,1,1,1,0}},
                         
                        {{1,1,1,1,1},
                         {1,1,1,1,1},
                         {1,1,1,1,1},
                         {1,1,1,1,1},
                         {1,1,1,1,1},
                         {1,1,1,1,1},
                         {1,1,1,1,1}},};

void loop() {

  // high frequency loop for displaying LED grid
  if(digitalRead(cpPin) == LOW) {
    
    // just before triggering clock (cpPin from LOW to HIGH)
    if(row_idx == 0){
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }

    delay(2); // just to make sure shift rigesture get it's value

    // parallels write from arduino to LED column
    digitalWrite(c0Pin, digits[digit][row_idx][0]);
    digitalWrite(c1Pin, digits[digit][row_idx][1]);
    digitalWrite(c2Pin, digits[digit][row_idx][2]);
    digitalWrite(c3Pin, digits[digit][row_idx][3]);
    digitalWrite(c4Pin, digits[digit][row_idx][4]);

    // and clock will trigger shift register to parallels write to LED rows
    digitalWrite(cpPin, HIGH);

    // next row index
    row_idx = (row_idx+1) % 7;
    
  } else {
    //set clock back to low
    digitalWrite(cpPin, LOW);
  }

  // read the state of the pushbutton value and set onboard LED:
  buttonState = digitalRead(buttonPin);
  
  // run this once the morse code is finised
  if (location == 5) {
      // convert morse code to number
      digit = morseToNumber();
      Serial.println(digit);

      // reset morse reader
      location = 0; 
      for (int i = 0; i < 5; i++) {
        morse[i] = 0;
      }
  }
  else if (location < 5) {
    // Start counting the length of state high once button is pressed
    if (buttonState == HIGH) {
      highCount++;
    }
    // button is released
    else {
      // if it is a short burst of 'high' state, count as a dot
      // minimum count of 10 to avout small debouncing problem
      if (highCount > 10 && highCount <= 200) {
        morse[location++] = 0;
      }
      // if it is a long burst, count as a dash
      else if (highCount > 200) {
        morse[location++] = 1;
      }

      // Check whether the current morse read is a valid number
      if (!checkMorseValidity()) {
        Serial.println("Invalid Morse Code");

        // if it's not, reser the morse scanner
        location = 0; 
        for (int i = 0; i < 5; i++) {
          morse[i] = 0;
        }

        // show an "X" on the LED
        digit = 10;
      }

      // reset the high state count
      highCount = 0;
    }
  }
}

// if there is a gap in between two dots/dashes (e.g dot-dash-dot), then the morse code cannot be valid
bool checkMorseValidity() {
  int lastMorse = location - 1;
  if (morse[lastMorse] == morse[0]) {
    if (lastMorse > 1) {
      for (int i = 1; i < lastMorse; i++) {
        if (morse[lastMorse] != morse[i]) {
          return false;
        }
      }
    }
  }
  return true;
}

// transform the morse code array to the number
int morseToNumber() {
  int total = 0;
  int number = 0;
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
  return number;
}