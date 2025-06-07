#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int soilMoisturePin = A0;
int soilMoistureValue = 0;
int led01 = 9;
int relayPin = 8;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(led01, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Soil moisture Data:");
}

void loop() {
  soilMoistureValue = analogRead(soilMoisturePin);

  if (soilMoistureValue <= 400) {
    digitalWrite(led01, HIGH);
    digitalWrite(relayPin, LOW);
  } else {
    digitalWrite(led01, LOW);
    digitalWrite(relayPin, HIGH);
  }

  lcd.setCursor(0, 1);
  lcd.print("Moisture: ");
  lcd.print(soilMoistureValue);
  lcd.print("     ");

  Serial.print("Sensor Value: ");
  Serial.println(soilMoistureValue);

  delay(1000);
}
