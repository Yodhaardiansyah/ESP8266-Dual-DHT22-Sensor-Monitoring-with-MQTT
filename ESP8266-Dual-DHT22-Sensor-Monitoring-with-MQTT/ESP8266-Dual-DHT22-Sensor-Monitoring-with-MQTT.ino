/*
 * ESP8266 Dual DHT22 Sensor Monitoring with MQTT
 * 
 * Author: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 * 
 * Description:
 * This program reads temperature and humidity from two DHT22 sensors and 
 * sends the data to an MQTT broker. If the connection fails multiple times, 
 * it attempts to reconnect to WiFi and MQTT.
 */

#include <ESP8266WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>  // MQTT Library

// WiFi Configuration (Sensitive data hidden)
const char* ssid = "your_wifi_ssid";     // Replace with your WiFi SSID
const char* password = "your_wifi_password"; // Replace with your WiFi Password

// DHT Sensor Configuration
#define DHTTYPE DHT22
#define DHTPIN1 14  // GPIO for first sensor (D5 on NodeMCU)
#define DHTPIN2 13  // GPIO for second sensor (D7 on NodeMCU)

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

// MQTT Configuration (Sensitive data hidden)
const char* mqttServer = "your_mqtt_server";   // Replace with your MQTT Server
const int mqttPort = 1883;                     // Default MQTT port
const char* mqttUser = "your_mqtt_username";   // Replace with your MQTT username
const char* mqttPassword = "your_mqtt_password"; // Replace with your MQTT password
const char* topic1 = "your_topic/dht1";        // MQTT topic for sensor 1
const char* topic2 = "your_topic/dht2";        // MQTT topic for sensor 2

WiFiClient espClient;
PubSubClient client(espClient);

int mqttFailureCount = 0;  // Counter for MQTT failures
const int maxFailures = 5; // Max failures before restarting WiFi

void connectWiFi() {
  Serial.println();
  Serial.print("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT!");
    } else {
      Serial.print("Failed, error code: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize sensors
  dht1.begin();
  dht2.begin();

  // Connect to WiFi
  connectWiFi();

  // Connect to MQTT Broker
  client.setServer(mqttServer, mqttPort);
  connectMQTT();
}

void loop() {
  client.loop();  // Maintain MQTT connection

  // Read temperature and humidity from both sensors
  float humidity1 = dht1.readHumidity();
  float temperature1 = dht1.readTemperature();
  float humidity2 = dht2.readHumidity();
  float temperature2 = dht2.readTemperature();

  bool success = true;

  if (!isnan(humidity1) && !isnan(temperature1)) {
    // Create JSON payload for Sensor 1
    String payload1 = "{";
    payload1 += "\"humidity\": " + String(humidity1) + ",";
    payload1 += "\"temperature\": " + String(temperature1);
    payload1 += "}";

    // Publish data to MQTT topic for Sensor 1
    if (!client.publish(topic1, payload1.c_str())) {
      Serial.println("Failed to send data for Sensor 1");
      success = false;
    } else {
      Serial.println("Sensor 1 Data Sent: " + payload1);
    }
  } else {
    Serial.println("Failed to read data from Sensor 1");
    success = false;
  }

  if (!isnan(humidity2) && !isnan(temperature2)) {
    // Create JSON payload for Sensor 2
    String payload2 = "{";
    payload2 += "\"humidity\": " + String(humidity2) + ",";
    payload2 += "\"temperature\": " + String(temperature2);
    payload2 += "}";

    // Publish data to MQTT topic for Sensor 2
    if (!client.publish(topic2, payload2.c_str())) {
      Serial.println("Failed to send data for Sensor 2");
      success = false;
    } else {
      Serial.println("Sensor 2 Data Sent: " + payload2);
    }
  } else {
    Serial.println("Failed to read data from Sensor 2");
    success = false;
  }

  // If failed, increment counter
  if (!success) {
    mqttFailureCount++;
    Serial.println("MQTT Failure Count: " + String(mqttFailureCount));
  } else {
    mqttFailureCount = 0; // Reset counter if success
  }

  // If failure count exceeds the limit, restart WiFi
  if (mqttFailureCount >= maxFailures) {
    Serial.println("Restarting WiFi connection...");
    WiFi.disconnect();
    connectWiFi();
    connectMQTT();
    mqttFailureCount = 0; // Reset counter after reconnect
  }

  // Wait before sending the next data
  delay(5000);  // Send data every 5 seconds
}
