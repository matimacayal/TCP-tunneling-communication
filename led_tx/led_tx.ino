#define ledPin 10
#define dataPin 9

unsigned int i = 10;
int sum = 1;
bool b = true;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(dataPin,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  analogWrite(dataPin,i);
  analogWrite(ledPin,i);
  delay(2);
  
  i = i + sum;
  if (i == 255) {
    sum = -1;
    //delay(1000);
  }
  else if (i == 0) {
    sum = 1;
    //delay(1000);
  }
}

