int ldrPin = A1;      
int ledPin = 9;        
int buzzerPin = 10;    

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));  
}

void loop() {
  int ldrValue = analogRead(ldrPin); 
  Serial.print("LDR Sensor: ");
  Serial.println(ldrValue);

  if (ldrValue < 100) {
    analogWrite(ledPin, 0);
    noTone(buzzerPin);
  } else {
    int brightness = map(ldrValue, 100, 1023, 150, 255);
    brightness = constrain(brightness, 150, 255);

    int blinkTime = random(50, 200);
    analogWrite(ledPin, brightness);
    delay(blinkTime);
    analogWrite(ledPin, 0);
    delay(random(50, 150));

    int freq = map(ldrValue, 100, 1023, 500, 1500);
    freq = constrain(freq, 500, 1500);
    int toneDuration = random(100, 300);
    tone(buzzerPin, freq, toneDuration);
    delay(toneDuration);
    noTone(buzzerPin);
  }

  delay(50);
}
