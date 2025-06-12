int SmokeSensorPin = 2;
int relayPin = 8;

void setup(){
  pinMode(SmokeSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  int sensorValue = digitalRead(SmokeSensorPin);

  Serial.print("Water Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue == LOW) { 
    Serial.println("Smoke is NOT Detect!");
    digitalWrite(relayPin, HIGH); 
  } else {
    Serial.println("Smoke Detect.");
    digitalWrite(relayPin, LOW); 
  }

  delay(1000);
}