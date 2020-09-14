int latchPin = 11;
int clockPin = 10;
int dataPin = 12;

int load = 5;
int clockEnable = 4;
int clockIn = 6;
int dataIn = 7;

byte buttons = 0;

void setup() {
  // shift out register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // shift in register
  pinMode(load, OUTPUT);
  pinMode(clockEnable, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  // write pulse to load pin
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  // Get data from 74HC165
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnable, LOW);
  buttons = ~shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnable, HIGH);

  Serial.println(buttons, BIN);
  
  updateShiftOutRegister();
  
  delay(20);
}

void updateShiftOutRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, buttons);
  digitalWrite(latchPin, HIGH);
}
