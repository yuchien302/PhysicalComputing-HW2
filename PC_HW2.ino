
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



int digits[10][7][5] = {{{0,0,0,0,0},
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
                         {0,0,0,0,0}}};

int digit = 0;

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


  // Demo how to control LED grid by setting global variable "digit"
  if (Serial.available() > 0) {
      int incomingByte = Serial.read();
      digit = incomingByte - '0';      
  }


  
  // read the state of the pushbutton value and set onboard LED:
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
