int ldrPin = A1;
int ledPin = 9;
int buzzerPin = 10;

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR Sensor: ");
  Serial.println(ldrValue);

  if (ldrValue < 200) {
    analogWrite(ledPin, 0);
    analogWrite(buzzerPin, 0);
  } else {
    int pwmValue = map(ldrValue, 200, 1023, 0, 255);
    pwmValue = constrain(pwmValue, 0, 255);

    analogWrite(ledPin, pwmValue);
    analogWrite(buzzerPin, pwmValue);
  }

  delay(500);
}
