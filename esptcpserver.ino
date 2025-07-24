#include <WiFi.h>

// Create Wi-Fi AP credentials
const char* ssid = "ESP32_Master";
const char* password = "password";
int led_state = 0;
WiFiServer server(80);  // TCP server on port 80

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);  // Set up Access Point
  
  server.begin(); // Start the TCP server
  Serial.println("TCP server started");
}

void loop() {
  WiFiClient client = server.available();   // Check for incoming clients
  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String data = client.readString();
        Serial.println("Received data: " + data);
        client.println("Hello from Master"); // Send response to the slave
        
        client.println(led_state);

        Serial.println(led_state);
        

      }
      
    }
    led_state = !led_state;
    client.stop();
    Serial.println("Client disconnected");
  }
}
