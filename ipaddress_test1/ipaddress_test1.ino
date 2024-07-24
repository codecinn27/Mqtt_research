#include <WiFi.h>

// Replace with your network credentials
// const char* ssid = "RUT901_246F";
// const char* password = "SiotWifiPassword2020";

const char* ssid = "Hee Wifi";
const char* password = "423619no26";

// Static IP configuration

IPAddress staticIP(192, 168, 50, 60); // ESP32 static IP
IPAddress gateway(192, 168, 50, 1);    // IP Address of your network gateway (router)
IPAddress subnet(255, 255, 255, 0);   // Subnet mask
// IPAddress primaryDNS(10, 10, 120, 1); // Primary DNS (optional)
// IPAddress secondaryDNS(0, 0, 0, 0);   // Secondary DNS (optional)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Configuring static IP
  // if(!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    if(!WiFi.config(staticIP, gateway, subnet)) {
    Serial.println("Failed to configure Static IP");
  } else {
    Serial.println("Static IP configured!");
  }
  
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Print the ESP32 IP address to Serial Monitor
}

void loop() {
  // Nothing to do here
}