//server
#include <WiFi.h>
#include <WebServer.h>

// Set your Access Point credentials
const char* ssid = "ESP32_HTTP_AP";
const char* password = "123456789Password";

// Create a web server object that listens for HTTP request on port 80
WebServer server(80);

const int ledPin = 2; // Onboard LED pin

// Function to handle the "GET /send?value=XX" request
void handleSendData() {
  // Check if the parameter "value" is present in the URL
  if (server.hasArg("value")) {
    String valueStr = server.arg("value");
    int receivedValue = valueStr.toInt();
   
    Serial.print("HTTP GET Received Value: ");
    Serial.println(receivedValue);
   
    // Respond back to the client to confirm receipt
    server.send(200, "text/plain", "Data received: " + valueStr);
   
    // Check if the number meets your condition
    if (receivedValue > 50) {
      Serial.println("Value > 50! Blinking LED 4 times...");
      blinkLED(4);
    } else {
      Serial.println("Value is 50 or less. No action.");
    }
  } else {
    // If the client accessed /send but forgot the parameter
    server.send(400, "text/plain", "Bad Request: Missing 'value' parameter");
  }
}

// Function to handle 404 (Not Found) errors
void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("\nSetting up Access Point...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Link the URL path "/send" to the handleSendData function
  server.on("/send", HTTP_GET, handleSendData);
  server.onNotFound(handleNotFound);

  // Start the server
  server.begin();
  Serial.println("HTTP Server started.");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
  }

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
