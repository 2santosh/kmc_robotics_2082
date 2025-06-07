int rainSensorPin = 3;
int ledPin = 4;
int rainValue;

void setup(){
  pinMode(rainSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  rainValue = digitalRead(rainSensorPin);
  if(rainValue == LOW){
    digitalWrite(ledPin, HIGH);
    Serial.println("Object Detected ! ");
  }else{
    digitalWrite(ledPin, LOW);
    Serial.println("NO Object.");
  }
  delay(200);
}