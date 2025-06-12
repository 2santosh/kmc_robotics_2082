// STA Mode

#include <ESP8266WiFi.h>

const char* ssid = "CodeHive1";
const char* password = "1234567891";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries <20) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  if(WiFi.status()==WL_CONNECTED){
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  }else{
    Serial.println("\nFailed to connect to WIFI.Check creadentials or singal.");
  }
}

void loop() {
  // Your main code here
}
