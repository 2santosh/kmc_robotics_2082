int IN1 = 2; 
int IN2 = 3; 
int ENA = 9; 

int IN3 = 4; 
int IN4 = 5; 
int ENB = 10;

int btnPin = 6;
int btnPin2 = 7;
int btnPin3 = 8;
int btnPin4 = 11; 

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(IN21, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(ENA2, OUTPUT);
  
  pinMode(IN23, OUTPUT);
  pinMode(IN24, OUTPUT);
  pinMode(ENB2, OUTPUT);

  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
}

void loop() {
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  analogWrite(ENA, 200);
  digitalWrite(LED_LEFT, HIGH);  
  
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  analogWrite(ENB, 200);
  digitalWrite(LED_RIGHT, HIGH); 

  delay(2000);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  delay(500);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  analogWrite(ENA, 200);
  digitalWrite(LED_LEFT, LOW);  
  
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  analogWrite(ENB, 200);
  digitalWrite(LED_RIGHT, LOW);  

  delay(2000);

  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);
  delay(500);
}
