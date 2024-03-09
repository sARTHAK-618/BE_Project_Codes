#include <WiFi.h>

const char* ssid = "Indu";
const char* password = "seahawks";

WiFiServer server(80);

int ledPin = 2; // GPIO pin connected to the LED
bool ledState = false; // State of the LED, initially off

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New client connected.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/plain");
            client.println();

            // If LED is off, turn it on
            if (!ledState) {
              digitalWrite(ledPin, HIGH);
              ledState = true;
              Serial.println("LED turned ON");
              client.println("LED turned ON");
            } 
            // If LED is on, turn it off
            else {
              digitalWrite(ledPin, LOW);
              ledState = false;
              Serial.println("LED turned OFF");
              client.println("LED turned OFF");
            }
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected.");
  }
}
