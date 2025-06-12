int lowSensor = 2;
int midSensor = 3;
int fullSensor = 4;

int lowLED = 5;
int midLED = 6;
int fullLED = 7;

void setup() {
  pinMode(lowSensor, INPUT);
  pinMode(midSensor, INPUT);
  pinMode(fullSensor, INPUT);

  pinMode(lowLED, OUTPUT);
  pinMode(midLED, OUTPUT);
  pinMode(fullLED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  bool low = digitalRead(lowSensor);
  bool mid = digitalRead(midSensor);
  bool full = digitalRead(fullSensor);

  digitalWrite(lowLED, LOW);
  digitalWrite(midLED, LOW);
  digitalWrite(fullLED, LOW);

  if (full == LOW) {
    Serial.println("Tank is FULL!");
    blinkLED(fullLED);
  } else if (mid == LOW) {
    Serial.println("Tank is HALF full.");
    blinkLED(midLED);
  } else if (low == LOW) {
    Serial.println("Tank is LOW.");
    blinkLED(lowLED);
  } else {
    Serial.println("Tank is EMPTY.");
  }

  delay(1000);
}

void blinkLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
  delay(300);
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
}
