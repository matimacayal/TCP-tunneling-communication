#define digitalRx 7
#define analogRx A0
#define ledPin 10        //Onboard LED = digital pin 13

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(analogRx));
  digitalWrite(ledPin, digitalRead(digitalRx));
}

