int WaterSensorPin = 2;
int relayPin = 8;

void setup(){
  pinMode(WaterSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  int sensorValue = digitalRead(WaterSensorPin);

  Serial.print("Water Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue == LOW) { 
    Serial.println("Tank is NOT FULL!");
    digitalWrite(relayPin, HIGH); 
  } else {
    Serial.println("Tankis FULL.");
    digitalWrite(relayPin, LOW); 
  }

  delay(1000);
}