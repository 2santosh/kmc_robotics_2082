int irSensorPin = 3;
int ledPin = 4;
int irValue;

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  irValue = digitalRead(irSensorPin);

  if (irValue == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Object detected!");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("No object.");
  }

  delay(200);
}
