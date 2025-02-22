## **ESP8266 Dual DHT22 Sensor Monitoring with MQTT**  

### **Author:**  
Yodha Ardiansyah  
Website: [arunovasi.my.id](https://arunovasi.my.id)  

### **Description**  
This project uses an **ESP8266 (NodeMCU)** to read temperature and humidity data from **two DHT22 sensors** and sends the data to an **MQTT broker**. If the connection fails multiple times, the system will attempt to **reconnect to WiFi and MQTT** automatically.  

### **Features**  
✅ Reads **temperature** and **humidity** from two DHT22 sensors  
✅ Publishes data to **MQTT broker**  
✅ Implements **auto-reconnect** mechanism for WiFi and MQTT  
✅ Uses **JSON format** for MQTT data  
✅ **Failsafe mechanism**: If MQTT fails 5 times, the device restarts the connection  

---

## **Hardware Requirements**  
- **ESP8266 (NodeMCU)**  
- **Two DHT22 Sensors**  
- **Jumper Wires**  
- **5V Power Supply**  

---

## **Software Requirements**  
- **Arduino IDE** (or PlatformIO)  
- **DHT Sensor Library** ([Download Here](https://github.com/adafruit/DHT-sensor-library))  
- **PubSubClient Library (MQTT)** ([Download Here](https://github.com/knolleary/pubsubclient))  

---

## **Circuit Diagram**  

| **Component** | **NodeMCU Pin** |
|--------------|---------------|
| **DHT22 Sensor 1** (Data) | **D5 (GPIO 14)** |
| **DHT22 Sensor 2** (Data) | **D7 (GPIO 13)** |
| **DHT22 VCC** | **3.3V** |
| **DHT22 GND** | **GND** |

---

## **Installation Steps**  

### **1. Install Required Libraries**  
In **Arduino IDE**, go to **Library Manager** and install:  
- **DHT Sensor Library** (by Adafruit)  
- **Adafruit Unified Sensor**  
- **PubSubClient**  

### **2. Modify WiFi and MQTT Settings**  
Open the `.ino` file and update the following lines with your credentials:  

```cpp
// WiFi Configuration
const char* ssid = "your_wifi_ssid";     
const char* password = "your_wifi_password"; 

// MQTT Configuration
const char* mqttServer = "your_mqtt_server";   
const int mqttPort = 1883;                     
const char* mqttUser = "your_mqtt_username";   
const char* mqttPassword = "your_mqtt_password"; 
const char* topic1 = "your_topic/dht1";        
const char* topic2 = "your_topic/dht2";        
```

### **3. Upload Code to ESP8266**  
- Connect ESP8266 to your PC  
- Select **Board: "NodeMCU 1.0 (ESP-12E Module)"**  
- Select the correct **COM Port**  
- Click **Upload**  

---

## **MQTT Data Format**  

Each sensor's data is sent as **JSON format**:

### **Example MQTT Payload for Sensor 1:**
```json
{
  "humidity": 60.5,
  "temperature": 25.3
}
```

### **Example MQTT Payload for Sensor 2:**
```json
{
  "humidity": 58.2,
  "temperature": 24.9
}
```

---

## **Troubleshooting**  
### **1. No Data in MQTT Broker**  
✅ Check MQTT connection logs in the **Serial Monitor**  
✅ Ensure the MQTT **username/password** is correct  
✅ Try reconnecting to the broker using **MQTT Explorer**  

### **2. WiFi Connection Fails**  
✅ Verify **WiFi SSID and Password** are correct  
✅ Move ESP8266 closer to the router  

### **3. Sensor Data Shows NaN (Not a Number)**  
✅ Check wiring: Ensure **Data Pin** is properly connected  
✅ Add a **4.7kΩ pull-up resistor** between **VCC and Data Pin**  

---

## **Future Improvements**  
🔹 Add **Blynk or Web Dashboard** for real-time monitoring  
🔹 Use **secure MQTT (TLS/SSL)** for better security  
🔹 Implement **deep sleep** mode to save power  

---

## **Credits**  
🚀 Developed by **Yodha Ardiansyah**  
🌐 Website: [arunovasi.my.id](https://arunovasi.my.id)  
📧 Contact: **yodha@arunovasi.my.id**  

---

Let me know if you need further modifications! 🚀
