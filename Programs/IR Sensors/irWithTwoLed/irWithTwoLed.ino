int irSensorPin = 10;

int normalBuzzerPin = 8;
int ambulanceBuzzerPin = 9;

int normalLed1 = 4;
int normalLed2 = 6;

int ambulanceLed1 = 5;
int ambulanceLed2 = 11;

int irValue;

void setup() {
  pinMode(irSensorPin, INPUT);

  pinMode(normalLed1, OUTPUT);
  pinMode(normalLed2, OUTPUT);
  pinMode(ambulanceLed1, OUTPUT);
  pinMode(ambulanceLed2, OUTPUT);
  pinMode(normalBuzzerPin, OUTPUT);
  pinMode(ambulanceBuzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  irValue = digitalRead(irSensorPin);

  if (irValue == LOW) {
    bool ambulanceDetected = false; 

    if (ambulanceDetected) {
      digitalWrite(ambulanceLed1, HIGH);
      delay(200);

      digitalWrite(ambulanceLed2, HIGH);
      digitalWrite(ambulanceBuzzerPin, HIGH);

      digitalWrite(normalLed1, LOW);
      digitalWrite(normalLed2, LOW);
      digitalWrite(normalBuzzerPin, LOW);

      Serial.println("Ambulance detected!");
    } else {
      digitalWrite(normalLed1, HIGH);
      delay(20);
      digitalWrite(normalLed2, HIGH);
      digitalWrite(normalBuzzerPin, HIGH);

      digitalWrite(ambulanceLed1, LOW);
      digitalWrite(ambulanceLed2, LOW);
      digitalWrite(ambulanceBuzzerPin, LOW);

      Serial.println("Object detected!");
    }
  } else {
    digitalWrite(normalLed1, LOW);
    digitalWrite(normalLed2, LOW);
    digitalWrite(ambulanceLed1, LOW);
    digitalWrite(ambulanceLed2, LOW);
    digitalWrite(normalBuzzerPin, LOW);
    digitalWrite(ambulanceBuzzerPin, LOW);

    Serial.println("No object.");
  }

  delay(200);
}
