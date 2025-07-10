# An open-source, modular IIoT-based SCADA system featuring InfluxDB-powered telemetry, edge processing, and AI-driven energy forecasting.

This project implements a scalable, real-time, IIoT-enabled SCADA system designed for intelligent process monitoring and predictive energy management. Leveraging open-source platforms such as Arduino Uno R4 WiFi, Node-RED, InfluxDB, and MATLAB/Python, this system exemplifies the integration of edge computing, cloud-based data storage, and AI-driven predictive analytics. 
![Node-RED Flow and Dashboard](noderedui.png)

## 🔍 Overview

This project demonstrates the design and implementation of a real-time industrial monitoring system leveraging:

- **InfluxDB** for high-resolution time-series telemetry logging  
- **MQTT + Node-RED** for data orchestration and dashboarding  
- **Arduino Uno R4 Wi-Fi** for sensor data acquisition  
- **Raspberry Pi** as the edge compute platform  
- **Scikit-learn + Streamlit** for AI-based energy prediction  

Designed for **low-cost**, **scalable**, and **energy-aware** automation in industrial environments.

## 🔧 System Architecture

The solution follows a modular, three-layer architecture 
![Node-RED Flow and Dashboard](System.jpg)
- **Sensing Layer:** Arduino Uno R4 WiFi collects real-time process data (temperature, current) via DS18B20 and ACS712 sensors.
- **Network Layer:** Data is streamed over MQTT to a Raspberry Pi edge node running Node-RED.
- **Application Layer:** Node-RED handles flow logic, visualization, and anomaly detection; data is logged to InfluxDB and used for AI model training in MATLAB/ Python.

⚡ Features
✅ Real-time process/environment telemetry ingestion
✅ Edge-based orchestration and local control
✅ InfluxDB time-series data retention and visualization
✅ Predictive analytics using Scikit-learn
✅ Web-based interface via Streamlit for live inference
✅ Lightweight and replicable for SMEs and research labs

📊 InfluxDB Usage
Schema: timestamp, ProcTemp, EnvTemp, Current, Energy
Retention: Configurable for historical trend analysis and AI training
Querying: Used for model development and system diagnostics

## 📷 Node-RED Flow

![Node-RED Flow and Dashboard](noderedflow.png)

## 🚀 How to Deploy

1. Flash Arduino with provided `.ino` code.
2. Install Node-RED on Raspberry Pi and import the provided flow.
3. Set up InfluxDB bucket and API token.
4. Configure the OpenWeatherMap API key in the flow.
5. Run the system and access the live dashboard via `http://<raspberry_pi_ip>:1880/ui`.

## 🛡️ Security Features

- MQTT with username/password authentication
- Network isolation and MAC filtering
- Token-based InfluxDB authentication
- Email-based anomaly alerts with time-based throttling

## 🤝 Acknowledgements

Adewale F. Ogabi developed this work at Teesside University under the School of Computing, Engineering and Information Sciences.
