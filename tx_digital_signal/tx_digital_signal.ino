#define dataPin 9
bool cero[6] = {1, 0, 0, 0, 1, 0};
bool uno[6] = {1, 0, 1, 0, 1, 0};

bool dig_signal[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int ds_len;

int i;
int j;

uint16_t tictoc;

void setup() {
  pinMode(dataPin,OUTPUT);
  ds_len = sizeof(dig_signal);
}

void loop() {
  for (i = 0; i < ds_len; i++) {
    tictoc = micros();
    if (dig_signal[i]) {
      for (j = 0; j < 6; j++) {
        digitalWrite(dataPin,uno[j]);
        delay(5);
      }
    }
    else {
      for (j = 0; j < 6; j++) {
        digitalWrite(dataPin,cero[j]);
        delay(5);
      }
    }
  }
}
