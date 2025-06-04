int ldrPin = A1;  

void setup() {
  pinMode(ldrPin, INPUT);       
  Serial.begin(9600);          
}

void loop() {
  int ldrValue = analogRead(ldrPin); 
  Serial.print("LDR Sensor:");
  Serial.println(ldrValue);          
  delay(500);                      
}
