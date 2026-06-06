#include <WiFi.h>
#include <NetworkClient.h>

// WiFi network credentials matching your Access Point
const char *ssid = "helloworld";
const char *password = "helloo12";

// The default IP for ESP32 SoftAP is usually 192.168.4.1
const char *serverAddress = "192.168.4.1"; 
const int serverPort = 80;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to network: ");
  Serial.println(ssid);

  // Initialize WiFi in Station mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address assigned to Client: ");
  Serial.println(WiFi.localIP());
}

void sendHTTPRequest(String requestPath) {
  NetworkClient client;

  Serial.print("Connecting to server at ");
  Serial.println(serverAddress);

  // Attempt to connect to the Access Point's server
  if (!client.connect(serverAddress, serverPort)) {
    Serial.println("Connection to server failed.");
    return;
  }

  Serial.print("Sending request: ");
  Serial.println(requestPath);

  // Construct a standard HTTP GET request matching your AP server's expectations
  client.print(String("GET ") + requestPath + " HTTP/1.1\r\n" +
               "Host: " + serverAddress + "\r\n" +
               "Connection: close\r\n\r\n");

  // Read response from the server (optional, but good for debugging)
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      // Uncomment the line below if you want to print the full raw HTML response
      // Serial.println(line); 
    }
  }

  // Stop the client to free up resources
  client.stop();
  Serial.println("Client request completed and connection closed.");
  Serial.println("----------------------------------------");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // 1. Send request to turn the AP's LED ON
    Serial.println("Commanding AP to turn LED ON...");
    sendHTTPRequest("/H");
    delay(4000); // Keep it on for 4 seconds

    // 2. Send request to turn the AP's LED OFF
    Serial.println("Commanding AP to turn LED OFF...");
    sendHTTPRequest("/L");
    delay(4000); // Keep it off for 4 seconds
  } else {
    Serial.println("WiFi disconnected. Reconnecting...");
    WiFi.begin(ssid, password);
    delay(5000);
  }
}