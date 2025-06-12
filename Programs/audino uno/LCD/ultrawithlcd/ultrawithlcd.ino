#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int trigpin = 2;
int echopin = 3;

LiquidCrystal_I2C lcd(0x27, 16, 2);
long duration;
long distance;

void setup() {

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);      
  lcd.print("Ultra Sensor Distance:"); 
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = duration * 0.034 / 2;
if(distance <= 30){
  lcd.setCursor(0, 1);
  lcd.println("Near: ");
  lcd.print(distance);
  lcd.print(" cm");
}
else{
  lcd.setCursor(0, 1);
  lcd.println("Far: ");

  lcd.print(distance);
  lcd.print(" cm");

}
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}