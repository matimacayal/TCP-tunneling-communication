/* Pseudo-código para comunicación serial por el modulo rf */
/*                                                         */
//  --                            --
//  | Start |  Data (8 bit) | Stop | 
//  --                            --

// Depends on the board. Uno and Leonardo respectively
#define dataPort PORTD
#define dataPortPin PD7
/*#define dataPort PORTE
#define dataPortPin PE6*/

#define dataPin 7
#define signalPin 4
#define data_size 8 //bits of data in serial frame
#define bit_duration 1000

uint8_t i;
uint8_t datastream[8] = {1,0,1,1,0,0,1,0};
//uint8_t datastream[8] = {0,0,0,0,0,0,0,0};

void setup() {
  //Set dataPin as output
  pinMode(dataPin,INPUT);
  //DDRD |= 0b11111100;  // sets dig pins 7 to 2 as outputs (0,1-rx,tx)
  
  dataPort = 0b00000000;  // sets pins to cero

  //Set timer 0
  TCCR0A = 0; //timer registaers A/B to 0
  TCCR0B = 0;
  TCNT0 = 0; //counter to 0
  TCCR0B |= (1 << CS11 ) | (1 << CS10); // bits for 64 prescaler

  //Rx signal
  while (!(PIND & (1 << PD7))) {
    // Wait for Rx to start and shout...
  }
  pinMode(dataPin,OUTPUT);
  delayMicroseconds(1000);
}

void loop() {
  /* Start */
  //Pin...xx76543210
  dataPort = 0b10000000;
  /*//dataport |= (1<<PD7);
  //dataport |= _BV(PD7); //high // &= ~V(PD7); low*/
  
  /* Data */
  TCNT0 = 0; //tic;
  dataPort = (datastream[0] << dataPortPin);
  i = 1;
  while ( i < data_size ) {
    delayMicroseconds(bit_duration - 4*TCNT0);
    TCNT0 = 0;
    dataPort = (datastream[i] << dataPortPin);
    i++;
  }
  
  /* Stop */
  dataPort = 0b00000000; //dataPin = 0
  delayMicroseconds(bit_duration - 4*TCNT0);
}


