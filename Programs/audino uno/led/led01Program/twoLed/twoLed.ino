int led01 = 9;
int led02 = 8;

int state = 0; 
unsigned long previousMillis = 0;
const long onTime = 150;
const long offTime = 150;

bool isLedOn = false;

void setup() {
  pinMode(led01, OUTPUT);
  pinMode(led02, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (!isLedOn && (currentMillis - previousMillis >= offTime)) {
    isLedOn = true; 
    previousMillis = currentMillis;

    if (state == 0) {
      digitalWrite(led01, HIGH);
      digitalWrite(led02, LOW);
    } else {
      digitalWrite(led02, HIGH);
      digitalWrite(led01, LOW);
    }

  } else if (isLedOn && (currentMillis - previousMillis >= onTime)) {
    isLedOn = false;
    previousMillis = currentMillis;

    digitalWrite(led01, LOW);
    digitalWrite(led02, LOW);

    if (state == 0) {
      state = 1;
    } else {
      state = 0;
    }
  }
}
