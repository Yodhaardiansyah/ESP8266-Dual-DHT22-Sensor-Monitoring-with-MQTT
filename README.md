# 🌱 **ESP8266 Dual DHT22 Sensor Monitoring with MQTT** 🚀  

📌 **Real-time temperature & humidity monitoring with automatic reconnect for stable data transmission!**  

---

## 🎯 **Project Overview**  
This project transforms your **ESP8266 (NodeMCU)** into a **wireless climate monitor**, collecting temperature & humidity data from **two DHT22 sensors** and sending it to an **MQTT broker**. If the connection drops, the system **automatically reconnects** to ensure smooth data logging.  

### ✨ **Why This Project?**  
✅ **Dual Sensor Support** – Monitor multiple locations at once  
✅ **Stable MQTT Connection** – Auto-reconnect prevents data loss  
✅ **JSON Format Data** – Clean & structured for easy processing  
✅ **Failsafe Mechanism** – Reconnects WiFi if MQTT fails multiple times  
✅ **Lightweight & Efficient** – Works with minimal power & data usage  

---

## 🛠 **Hardware Requirements**  
🔹 **ESP8266 (NodeMCU)**  
🔹 **Two DHT22 Sensors**  
🔹 **Jumper Wires**  
🔹 **5V Power Supply**  

### 🏗 **Wiring Setup**  

| **Component** | **NodeMCU Pin** |
|--------------|---------------|
| **DHT22 Sensor 1 (Data)** | **D5 (GPIO 14)** |
| **DHT22 Sensor 2 (Data)** | **D7 (GPIO 13)** |
| **DHT22 VCC** | **3.3V** |
| **DHT22 GND** | **GND** |

---

## 💻 **Software Requirements**  
📥 Install these libraries in **Arduino IDE**:  
✅ **DHT Sensor Library** ([Download](https://github.com/adafruit/DHT-sensor-library))  
✅ **Adafruit Unified Sensor**  
✅ **PubSubClient (MQTT)** ([Download](https://github.com/knolleary/pubsubclient))  

---

## 🔧 **How to Set Up & Run**  

### **1️⃣ Install Required Libraries**  
Open **Arduino IDE**, go to **Library Manager**, and install:  
📌 **DHT Sensor Library**  
📌 **PubSubClient**  

### **2️⃣ Update WiFi & MQTT Settings**  
Modify these lines in your code:  

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

### **3️⃣ Upload Code to ESP8266**  
🔌 Connect ESP8266 to your PC  
⚙️ Select **Board: "NodeMCU 1.0 (ESP-12E Module)"**  
🔍 Choose the correct **COM Port**  
🚀 Click **Upload**  

---

## 📡 **How Data is Sent to MQTT**  

Each sensor sends **JSON formatted** data to the MQTT broker:  

✅ **Example Payload for Sensor 1**  
```json
{
  "humidity": 60.5,
  "temperature": 25.3
}
```

✅ **Example Payload for Sensor 2**  
```json
{
  "humidity": 58.2,
  "temperature": 24.9
}
```

---

## 🛠 **Troubleshooting Guide**  

💥 **No Data in MQTT Broker?**  
✅ Check Serial Monitor for MQTT connection logs  
✅ Verify **MQTT username/password**  
✅ Use **MQTT Explorer** to debug  

📶 **WiFi Not Connecting?**  
✅ Ensure **SSID & Password** are correct  
✅ Move ESP8266 closer to the router  

🌡 **Sensor Data Shows NaN?**  
✅ Check wiring: Ensure **Data Pin** is properly connected  
✅ Add a **4.7kΩ pull-up resistor** between **VCC and Data Pin**  

---

## 🚀 **Future Enhancements**  
🔹 Integrate **Blynk or Web Dashboard** for live monitoring  
🔹 Upgrade to **secure MQTT (TLS/SSL)** for better security  
🔹 Implement **deep sleep mode** for energy efficiency  

---

## 👨‍💻 **Credits & Contact**  
🎯 **Developed by:** Yodha Ardiansyah  
🌐 **Website:** [arunovasi.my.id](https://arunovasi.my.id)  
📧 **Contact:** yodha@arunovasi.my.id  

💡 **Let's build smarter IoT solutions together!** 🚀
