// AP Mode

#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(115200);

  Wifi.softAP("MyESP_AP","12345678");
  Serial.print("Access Point started");
  Serial.print("IP Address:");
  Serial.print(WiFi.softAPIP());  
}

void loop(){
  
}