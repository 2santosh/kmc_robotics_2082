#include <ESP8266WiFi.h>

const char* ssid = "Dishhome";
const char* password = "Nothing123";

const int relayPin = 5;

WiFiServer server(80);
bool relayState = false;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client Connected.");
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        if (c == '\n') {
          Serial.print("Request: ");
          Serial.println(request);

          if (request.indexOf("/relay/on") != -1) {
            digitalWrite(relayPin, LOW); 
            relayState = true;
          }
          if (request.indexOf("/relay/off") != -1) {
            digitalWrite(relayPin, HIGH);
            relayState = false;
          }

          String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n";
          html += "<!DOCTYPE html><html><head>";
          html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
          html += "<title>Smart Relay Control</title>";
          html += "<style>";
          html += "body { font-family: sans-serif; background: #121212; color: #f0f0f0; text-align: center; padding: 20px; display:flex; flex-direction:column;align-content:space-around; flex-wrap:wrap;}";
          html += "h1 { font-size: 2.5em; margin-bottom: 20px; }";
          html += ".button { background: #1e88e5; border: none; color: white; padding: 16px 32px; text-decoration: none; font-size: 20px; margin: 10px; border-radius: 12px; transition: 0.3s;}";
          html += ".button:hover { background: #1565c0; }";
          html += ".status { margin-top: 20px; font-size: 1.4em; padding: 10px; border-radius: 10px; display: inline-block; }";
          html += ".on { background: #00c853; }";
          html += ".off { background: #d50000; }";
          html += "</style>";
          html += "</head><body>";
          html += "<h1>Smart Relay Control</h1>";

          html += "<a class='button' href='/relay/on'>Turn ON</a>";
          html += "<a class='button' href='/relay/off'>Turn OFF</a>";

          html += "<div class='status ";
          html += (relayState) ? "on'>Light is ON</div>" : "off'>Light is OFF</div>";

          html += "</body></html>";

          client.print(html);
          break;
        }
      }
    }

    delay(1); 
    client.stop();
    Serial.println("Client Disconnected.");
  }
}