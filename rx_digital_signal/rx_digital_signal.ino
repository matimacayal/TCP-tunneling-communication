#define dataPin A0

unsigned int data;

void setup() {
  pinMode(dataPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  data = digitalRead(dataPin);
  Serial.println(data);
  delay(5);
}
