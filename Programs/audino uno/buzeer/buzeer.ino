int led01 = 9;
int buzzer = 11;

void setup() {
  pinMode(led01, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  digitalWrite(led01, HIGH);   
  digitalWrite(buzzer, LOW);  
  delay(1000);               

  digitalWrite(led01, LOW);    
  digitalWrite(buzzer, HIGH);  
  delay(1000);                 
}
