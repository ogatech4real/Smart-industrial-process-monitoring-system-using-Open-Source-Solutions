# Smart Industrial Process Monitoring System Using Open-Source Solutions

This project implements a scalable, real-time, IIoT-enabled SCADA system designed for intelligent process monitoring and predictive energy management. Leveraging open-source platforms such as **Arduino Uno R4 WiFi**, **Node-RED**, **InfluxDB**, and **MATLAB**, this system exemplifies the integration of edge computing, cloud-based data storage, and AI-driven predictive analytics.

## 🔧 System Architecture

The solution follows a modular, three-layer architecture:
- **Sensing Layer:** Arduino Uno R4 WiFi collects real-time process data (temperature, current) via DS18B20 and ACS712 sensors.
- **Network Layer:** Data is streamed over MQTT to a Raspberry Pi edge node running Node-RED.
- **Application Layer:** Node-RED handles flow logic, visualization, and anomaly detection; data is logged to InfluxDB and used for AI model training in MATLAB.

## 🧩 Features

- 🔁 **Real-Time Data Acquisition** from industrial sensors
- 📊 **Live SCADA Dashboards** (Node-RED UI + historical charting)
- ☁️ **Time-Series Logging** using InfluxDB
- 🔮 **AI-Driven Predictive Analytics** via MATLAB regression models
- 🌡️ **Environmental Integration** using OpenWeatherMap API
- ⚠️ **Email Alerts** on process anomalies
- 🧠 **Energy Forecasting** for adaptive load management

## 📁 Project Structure
