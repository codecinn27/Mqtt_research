#include <WiFi.h>
#include <PubSubClient.h> //Nick O'Leary
#include <ESPmDNS.h>

// Replace with your network credentials
const char* ssid = "Hee Wifi";
const char* password = "423619no26";

// const char* ssid = "syswell";
// const char* password = "MLS@Syswell23";

// Static IP configuration
IPAddress staticIP(192, 168, 50, 60); // ESP32 static IP
IPAddress gateway(192, 168, 50, 1);    // IP Address of your network gateway (router)
IPAddress subnet(255, 255, 255, 0);   // Subnet mask
// IPAddress primaryDNS(192, 168, 50, 1); // Primary DNS (optional)
// IPAddress secondaryDNS(0, 0, 0, 0);   // Secondary DNS (optional)

// Device name
const char* deviceName = "Esp32_device";

// MQTT Broker settings
const char* mqtt_server = "192.168.50.191";
const char* mqtt_topic = "test/1";

WiFiClient espClient;
PubSubClient client(espClient);

int count = 1;
unsigned long lastMsg = 0;
#define MSG_INTERVAL 5000  // Message interval in milliseconds

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Configuring static IP
  // if (!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
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
  Serial.println(WiFi.localIP());

  // Advertise services
  MDNS.addService("mqtt", "tcp", 1883); // Example: advertise an MQTT service on port 1883
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  client.setServer(mqtt_server, 1883);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  unsigned long now = millis();
  if (now - lastMsg > MSG_INTERVAL) {
    lastMsg = now;
    
    // Create the message payload with incremented count
    String mqtt_message = "{ \"temperature\": 35, \"windspeed\": 23 , \"count\": " + String(count) + "}";
    count++;
    
    // Publish the message
    client.publish(mqtt_topic, mqtt_message.c_str());
    
    Serial.print("Message published: ");
    Serial.println(mqtt_message);
  }  
}
