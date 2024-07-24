#include <WiFi.h>
#include <ESPmDNS.h> //no need to add install any library is included with the ESP32 core for Arduino

// Replace with your network credentials
const char* ssid = "Hee Wifi";
const char* password = "423619no26";

// Static IP configuration
IPAddress staticIP(192, 168, 50, 60); // ESP32 static IP
IPAddress gateway(192, 168, 50, 1);    // IP Address of your network gateway (router)
IPAddress subnet(255, 255, 255, 0);   // Subnet mask

// Device name
const char* deviceName = "Esp32_device";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Configuring static IP
  if (!WiFi.config(staticIP, gateway, subnet)) {
    Serial.println("Failed to configure Static IP");
  } else {
    Serial.println("Static IP configured!");
  }

  // Start mDNS
  if (!MDNS.begin(deviceName)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Print the ESP32 IP address to Serial Monitor

  // Advertise services
  MDNS.addService("http", "tcp", 80); // Example: advertise an HTTP service on port 80
}

void loop() {
  // Nothing to do here
}
