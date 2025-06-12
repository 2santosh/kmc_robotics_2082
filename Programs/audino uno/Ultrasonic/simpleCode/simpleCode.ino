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

  
  if (distance <= 50 && distance >= 3 ) {
    Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);   
    delay(200);                      
    digitalWrite(ledPin, LOW);       
    digitalWrite(buzzerPin, LOW);    
  } else {
    digitalWrite(ledPin, LOW);       
    digitalWrite(buzzerPin, LOW);    
  }

   delay(300);
}
