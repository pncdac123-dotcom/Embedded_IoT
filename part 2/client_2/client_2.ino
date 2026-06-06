//client code
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32_HTTP_AP";
const char* password = "123456789Password";

// Base URL targeting the AP's IP and the /send path
const String serverPath = "http://192.168.4.1/send?value=";

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(34));

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWi-Fi connected!");
}

void loop() {
  // Check Wi-Fi connection status before making the request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Generate a random number between 10 and 99
    int randomNumber = random(10, 100); 
    
    // Combine base URL with the random number (e.g., "http://192.168.4.1/send?value=57")
    String fullURL = serverPath + String(randomNumber);
    
    Serial.print("Sending GET request to: ");
    Serial.println(fullURL);
    
    // Initialize the HTTP request with the target URL
    http.begin(fullURL);
    
    // Send the actual GET request
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      
      // Read the response payload from the server
      String payload = http.getString();
      Serial.print("Server reply: ");
      Serial.println(payload);
    } else {
      Serial.print("Error code on sending GET: ");
      Serial.println(httpResponseCode);
    }
    
    // Free resources used by the HTTP instance
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  
  // Wait 5 seconds before sending the next GET request
  delay(5000);
}
