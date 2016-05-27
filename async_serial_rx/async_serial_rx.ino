/* Pseudo-código para comunicación serial por módulo rf */
/*                                                      */
#define dataPin 7
#define signalPin 4
#define data_size 8
#define bit_duration 1000
#define lecture_offset bit_duration/4

uint8_t i;
uint8_t datastream[8];

void setup() {
  pinMode(dataPin,OUTPUT);

  //Set timer 0
  TCCR0A = 0; //timer registaers A/B to 0
  TCCR0B = 0;
  TCNT0 = 0; //counter to 0
  TCCR0B |= (1 << CS11 ) | (1 << CS10); // bits for 64 prescaler

  //Signal Tx
  PORTE = 0b10000000; //envío señal a Tx
  PORTE = 0b10000000; //mantengo la señal
  PORTE = 0b00000000;
  DDRE |= 0b00000000; //cambio el pin 7 a output


  while(!(PINE & (1 << PE6))) {
    //Espera flanco de subida...
  }
  delayMicroseconds(bit_duration);

  /* Data */
  delayMicroseconds(lecture_offset); //offset de lectura
  TCNT0 = 0;
  datastream[0] = (PINE & (1 << PE6));
  i = 1;
  while (i < data_size) {
    delayMicroseconds(bit_duration - 4*TCNT0); //delay(1000-toc)
    TCNT0 = 0; //tic
    datastream[i] = (PINE & (1 << PE6));
    i++;
  }

  //if (PIND & (1 << PD2)) {
  Serial.begin(9600);
  for (i = 0; i < data_size; i++) {
    Serial.print(datastream[i]);
    Serial.print(" ");
  }
  Serial.println(" end. Reset arduinos.");
  //}
}

void loop() {
  /* Start */
  for (i = 0; i < data_size; i++) {
    Serial.print(datastream[i]);
    Serial.print(" ");
  }
  Serial.println(" end. Reset arduinos.");
  
  /* Stop */
}

