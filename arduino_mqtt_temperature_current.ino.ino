#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>

// ---------------- PIN DEFINITIONS ----------------
#define TEMP_SENSOR_PIN 2     // DS18B20 Data IN2
#define ACS712_PIN A0         // Current Sensor
#define CONTROL_PIN 7         // Output control pin

#define VREF 5.0              // Reference voltage (5V for Arduino)
#define ADC_MAX 1023.0        // 10-bit ADC (0-1023)
#define ACS712_OFFSET 2.5     // Offset for calibration
#define SENSITIVITY 0.100     // For ACS712-20A

// ---------------- WIFI CONFIG -------------------
const char* ssid = "Decent"; //use the name of the wifi
const char* password = "88888888"; //wifi password

// ---------------- MQTT CONFIG -------------------
const char* mqtt_server = "172.20.10.7";  // Raspberry Pi's IP
const int mqtt_port = 1883;
const char* mqtt_topic = "sensors/data";

// ---------------- OBJECT DECLARATION ------------
WiFiClient wifiClient;
PubSubClient client(wifiClient);
OneWire ds(TEMP_SENSOR_PIN);

byte sensorAddress[8];  // Stores DS18B20 address

// ---------------- FUNCTION: READ TEMPERATURE ----
float readTemperature() {
  if (sensorAddress[0] == 0x00) {
    Serial.println("Sensor address not initialized!");
    return -127.0;
  }

  ds.reset();
  ds.select(sensorAddress);
  ds.write(0x44, 1);  // Start conversion
  delay(750);         // Wait for conversion
  ds.reset();
  ds.select(sensorAddress);
  ds.write(0xBE);     // Read scratchpad

  byte data[9];
  for (byte i = 0; i < 9; i++) data[i] = ds.read();

  int16_t raw = (data[1] << 8) | data[0];
  float celsius = (float)raw / 16.0;
  return celsius;
}

// ---------------- FUNCTION: READ CURRENT --------
float readCurrent() {
  int adcValue = analogRead(ACS712_PIN);
  float voltage = (adcValue / ADC_MAX) * VREF;
  float current = (voltage - ACS712_OFFSET) / SENSITIVITY;
  return current;
}

// ---------------- FUNCTION: CONNECT TO WIFI -----
void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ---------------- FUNCTION: CONNECT TO MQTT -----
void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ArduinoR4Client")) {
      Serial.println(" connected.");
    } else {
      Serial.print(" failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds.");
      delay(5000);
    }
  }
}

// ---------------- FUNCTION: INIT TEMP SENSOR -----
bool initializeTempSensor() {
  if (!ds.search(sensorAddress)) {
    Serial.println("DS18B20 not found!");
    return false;
  }

  Serial.print("Found DS18B20 with address: ");
  for (int i = 0; i < 8; i++) {
    Serial.print(sensorAddress[i], HEX);
    if (i < 7) Serial.print(":");
  }
  Serial.println();
  ds.reset_search();
  return true;
}

// ---------------- SETUP -------------------------
void setup() {
  Serial.begin(115200);
  pinMode(CONTROL_PIN, OUTPUT);

  connectToWiFi();
  client.setServer(mqtt_server, mqtt_port);

  // Initialize temperature sensor
  if (!initializeTempSensor()) {
    Serial.println("Halting due to DS18B20 failure.");
    while (true);  // Halt execution
  }
}

// ---------------- LOOP --------------------------
void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  float temperature = readTemperature();
  float current = readCurrent();

  // DEBUG: Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C | Current: ");
  Serial.print(current);
  Serial.print(" A | Status: ");

  if (temperature < 55.0) {
    digitalWrite(CONTROL_PIN, HIGH);
    Serial.println("ON");
  } else {
    digitalWrite(CONTROL_PIN, LOW);
    Serial.println("OFF");
  }

  // MQTT JSON Payload
  String payload = "{\"temperature\":" + String(temperature, 2) + ",\"current\":" + String(current, 2) + ",\"status\":\"" + String(temperature < 55.0 ? "ON" : "OFF") + "\"}";
  client.publish(mqtt_topic, payload.c_str());
  Serial.print("Publishing MQTT: ");
  Serial.println(payload);

  Serial.println("Publishing MQTT: " + payload);
  client.publish(mqtt_topic, payload.c_str());

  delay(5000);
}
