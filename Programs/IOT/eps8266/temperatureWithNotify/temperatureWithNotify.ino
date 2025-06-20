#define BLYNK_TEMPLATE_ID "TMPL61UkkOz0C"
#define BLYNK_TEMPLATE_NAME "temperatureHumidity"
#define BLYNK_AUTH_TOKEN "kb6-rKHFKcHPriBA5ezH7L5jRwWVow-z"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "Dishhome";
char pass[] = "Nothing123";

#define RELAY_PIN D1
#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

bool notificationSent = false;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(5000L, sendSensorData);
}

void sendSensorData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.println(humidity);

  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V4, humidity);

  if (temperature > 30.0) {
    if (!notificationSent) {
      Blynk.logEvent("high_temperature", String("High temperature: ") + temperature + "°C");
      notificationSent = true;
    }
  } else {
    notificationSent = false; 
  }
}

BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(RELAY_PIN, value);
  Serial.println(value == 1 ? "Relay ON" : "Relay OFF");
}

void loop() {
  Blynk.run();
  timer.run();
}
