#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "ThingSpeak.h"

const char* ssid = "Dishome";
const char* password = "Nothing123";

unsigned long channelID = 2988372;
const char* writeAPIKey = "5AZINL876Z2IOYH6";

WiFiClient client;

const int trigPin = 14;  
const int echoPin = 12;  

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  ThingSpeak.setField(1, distance);
  int x = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (x == 200) {
    Serial.println("Data sent to ThingSpeak.");
  } else {
    Serial.print("Error sending data. HTTP code: ");
    Serial.println(x);
  }

  delay(1500);
}
