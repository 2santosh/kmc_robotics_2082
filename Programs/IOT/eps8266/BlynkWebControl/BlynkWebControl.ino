#define BLYNK_TEMPLATE_ID "TMPL65HBPjPtP"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "3iZEkiAPa3XO88Rwd3f6vqzm9H-Cwt-8"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Dishhome";
char pass[] = "Nothing123";

int relayPin = D1;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  Serial.println("Relay set to LOW (OFF)");

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retries++;
    if (retries > 20) {
      Serial.println("\nFailed to connect to WiFi!");
      return;
    }
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(relayPin, value);
  Serial.print("Received V0: ");
  Serial.println(value);
  Serial.print("Relay turned ");
  Serial.println(value ? "ON" : "OFF");
}

void loop() {
  Blynk.run();
}
