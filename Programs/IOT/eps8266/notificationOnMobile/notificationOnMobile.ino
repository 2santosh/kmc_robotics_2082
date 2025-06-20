#define BLYNK_TEMPLATE_ID "TMPL61wxkDDeV"
#define BLYNK_TEMPLATE_NAME "allSensorNotification"
#define BLYNK_AUTH_TOKEN "6B_2z6gfSYSeGKL_TR7BeGaaoIVl238X"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIG_PIN D4  // GPIO2
#define ECHO_PIN D3  // GPIO0

char ssid[] = "Dishhome";
char pass[] = "Nothing123";

BlynkTimer timer;

bool objectNotified = false;

void setup() {
  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  // Wait for connection with timeout
  int timeout = 20; // 20 * 500ms = 10 seconds timeout
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  } else {
    Serial.println("\nWiFi connection failed!");
  }

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  timer.setInterval(5000L, checkUltrasonic);
}

void checkUltrasonic() {
  long distance = measureDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V0, distance);

  if (distance < 10) {
    if (!objectNotified) {
      Blynk.logEvent("findobject", "Object detected near sensor!");
      objectNotified = true;
      Serial.println("** Notification sent: Object detected! **");
    }
  } else {
    objectNotified = false;
  }
}

long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return 999; // no echo received (out of range)

  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  Blynk.run();
  timer.run();

  // Optional: show current WiFi status periodically
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 10000) { // every 10 seconds
    lastPrint = millis();
    Serial.print("WiFi status: ");
    switch (WiFi.status()) {
      case WL_CONNECTED: Serial.println("Connected"); break;
      case WL_NO_SSID_AVAIL: Serial.println("SSID not available"); break;
      case WL_CONNECT_FAILED: Serial.println("Connection Failed"); break;
      case WL_DISCONNECTED: Serial.println("Disconnected"); break;
      default: Serial.println("Unknown"); break;
    }
  }
}
