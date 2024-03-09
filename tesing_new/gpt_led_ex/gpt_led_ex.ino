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
            client.println("Content-type:text/html");
            client.println();

            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP32 LED Control</title></head>");
            client.println("<body><h1>ESP32 LED Control</h1>");

            // If LED is off, display a button to turn it on
            if (!ledState) {
              client.println("<p><a href=\"/on\"><button>Turn LED ON</button></a></p>");
            } 
            // If LED is on, display a button to turn it off
            else {
              client.println("<p><a href=\"/off\"><button>Turn LED OFF</button></a></p>");
            }
            client.println("</body></html>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        // If client requests to turn LED on
        if (currentLine.endsWith("GET /on")) {
          digitalWrite(ledPin, HIGH);
          ledState = true;
          Serial.println("LED turned ON");
        }
        // If client requests to turn LED off
        else if (currentLine.endsWith("GET /off")) {
          digitalWrite(ledPin, LOW);
          ledState = false;
          Serial.println("LED turned OFF");
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected.");
  }
}