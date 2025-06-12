int trigpin = 3;
int echopin = 4;
int ledPin = 5;
int buzzerPin = 8;

long duration;
long distance;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance <= 50 && distance >= 3) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    digitalWrite(ledPin, HIGH);

    // War siren effect - rising and falling tone
    for (int i = 500; i <= 1000; i += 10) {
      tone(buzzerPin, i);
      delay(5);
    }
    for (int i = 1000; i >= 500; i -= 10) {
      tone(buzzerPin, i);
      delay(5);
    }

    noTone(buzzerPin);  // Stop the buzzer
    digitalWrite(ledPin, LOW);

  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);  // Ensure buzzer is off
  }

  delay(200);
}
