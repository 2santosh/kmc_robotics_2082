#include <ESP8266WiFi.h>

const char* ssid = "CodeHive1";
const char* password = "1234567891";
const char* ap_ssid = "CodeHive2";
const char* ap_password = "12345678";

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi. Starting Access Point...");
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_password);
    delay(100); 
    Serial.print("Access Point started with IP: ");
    Serial.println(WiFi.softAPIP());
  }
}

void loop() {
  // Your main loop code here
}
