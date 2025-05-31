int trigpin = 3;
int echopin = 4;
int trigpin1 = 7;
int echopin1 = 9;

int ledPin1 = 5;
int ledPin2 = 6;

int buzzerPin = 8;

long duration;
long distance;

long duration1;
long distance1;

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(trigpin1, OUTPUT);
  pinMode(echopin1, INPUT);  // fixed missing closing parenthesis
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Sensor 1
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;

  // Sensor 2
  digitalWrite(trigpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1, LOW);

  duration1 = pulseIn(echopin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  if (distance1 <= 50 && distance1 >= 3) {
    Serial.print("Sensor 2 Distance: ");
    Serial.print(distance1);
    Serial.println(" cm");

    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    noTone(buzzerPin);
  } 
  else if (distance <= 50 && distance >= 3) {
    Serial.print("Sensor 1 Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin1, LOW);

    tone(buzzerPin, 1800); 
    delay(100);
    noTone(buzzerPin);
    delay(100);
  } 
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    noTone(buzzerPin);
  }

  delay(200);
}
