#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11
#define DHTPIN 7                // D7 for DHT11 (Digital Pin)
#define SOIL_PIN A1             // A1 for Soil Moisture Sensor
#define LDR_PIN  A0             // A0 for LDR
#define LED_BRIGHTNESS_PIN 5    // D5
#define LED_FADE_PIN       6    // D6 (PWM)
#define AUDIO_PIN          9    // D9 (Piezo Buzzer)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int soilDryThreshold = 600;
int lightLowThreshold = 300;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BRIGHTNESS_PIN, OUTPUT);
  pinMode(LED_FADE_PIN, OUTPUT);
  pinMode(AUDIO_PIN, OUTPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();
}

int readSoilSensor() {
  int val = analogRead(SOIL_PIN);
  Serial.print("Soil: ");
  Serial.println(val);
  return val;
}

int readLDRSensor() {
  int val = analogRead(LDR_PIN);
  Serial.print("Light: ");
  Serial.println(val);
  return val;
}

void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  int soil = readSoilSensor();
  int light = readLDRSensor();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C H:");
  lcd.print(hum, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soil);
  lcd.print(" LDR:");
  lcd.print(light);

  if (soil > soilDryThreshold) {
    digitalWrite(LED_BRIGHTNESS_PIN, HIGH);
    tone(AUDIO_PIN, 1000);  // Play 1kHz tone
  } else {
    digitalWrite(LED_BRIGHTNESS_PIN, LOW);
    noTone(AUDIO_PIN);      // Stop tone
  }
}

void loop() {
  sendSensorData();

  // LED fade animation
  for (int val = 0; val <= 255; val += 5) {
    analogWrite(LED_FADE_PIN, val);
    delay(30);
  }
  for (int val = 255; val >= 0; val -= 5) {
    analogWrite(LED_FADE_PIN, val);
    delay(30);
  }
}
