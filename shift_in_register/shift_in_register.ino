int load = 5;
int clockEnable = 4;
int clockIn = 6;
int dataIn = 7;

void setup() {
  Serial.begin(9600);
  pinMode(load, OUTPUT);
  pinMode(clockEnable, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);
}

void loop() {
  // write pulse to load pin
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  // Get data from 74HC165
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnable, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnable, HIGH);

  // Print to serial monitor
  Serial.print("Pin States:  ");
  Serial.println(incoming, BIN);
  delay(200);
}
