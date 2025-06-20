#define BLYNK_TEMPLATE_ID "TMPL61wxkDDeV"
#define BLYNK_TEMPLATE_NAME "allSensorNotification"
#define BLYNK_AUTH_TOKEN "6B_2z6gfSYSeGKL_TR7BeGaaoIVl238X"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

#define SOIL_PIN A0

#define TRIG_PIN D4  // GPIO2 (Moved ultrasonic pins here)
#define ECHO_PIN D3  // GPIO0

#define SS_PIN D2    // RFID SDA (GPIO4) moved from D4
#define RST_PIN D1   // RFID RST (GPIO5) moved from D3

char ssid[] = "Dishhome";
char pass[] = "Nothing123";

BlynkTimer timer;
MFRC522 rfid(SS_PIN, RST_PIN);

bool systemStarted = false;
bool comboNotificationSent = false;
bool soilNotified = false;
bool objectNotified = false;

int mode = 0;

// Keypad setup 4x3
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {D0, D8, D6, D7};
byte colPins[COLS] = {D5, D4, D3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Initializes hardware SPI for RFID (SCK, MISO, MOSI)
  rfid.PCD_Init();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  timer.setInterval(5000L, readSensors);
}

bool checkRFID() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return false;

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  Serial.println("UID: " + uid);
  rfid.PICC_HaltA();

  // Replace with your actual RFID UID (uppercase, no spaces)
  if (uid == "YOUR_UID_HERE") {
    return true;
  }
  return false;
}

void handleKeypad() {
  char key = keypad.getKey();
  if (key && key >= '1' && key <= '2') {
    mode = key - '0';
    Serial.print("Mode selected: ");
    Serial.println(mode);
  }
}

void readSensors() {
  if (!systemStarted) return;

  handleKeypad();

  int soil = analogRead(SOIL_PIN);
  long distance = measureDistance();

  Serial.print("Soil: "); Serial.print(soil);
  Serial.print(" | Distance: "); Serial.println(distance);

  Blynk.virtualWrite(V1, soil);     // Gauge
  Blynk.virtualWrite(V0, distance); // Level

  if (mode == 2 && distance < 10 && soil < 500) {
    if (!comboNotificationSent) {
      Blynk.logEvent("both_alert", "Soil dry & object detected!");
      comboNotificationSent = true;
    }
  } else {
    comboNotificationSent = false;
  }

  if (mode == 2 && distance < 10 && !objectNotified) {
    Blynk.logEvent("object_detected", "Object detected near sensor!");
    objectNotified = true;
  } else if (distance >= 10) {
    objectNotified = false;
  }
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  Blynk.run();
  timer.run();

  if (!systemStarted && checkRFID()) {
    systemStarted = true;
    Serial.println("System Started");
  }
}
