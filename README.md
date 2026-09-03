

# IIoT Predictive Maintenance System

Ein IoT-basiertes System zur vorausschauenden Wartung (Predictive Maintenance). Ein ESP32 sammelt (simulierte) Sensordaten, sendet diese über MQTT an ein Python-Backend, wo ein Machine-Learning-Modell (Random Forest) die Daten auswertet und eine Status-LED am Mikrocontroller dynamisch steuert.

## Features
* **ESP32 MQTT-Client:** Liest Sensordaten aus einer CSV-Datei via SPIFFS und publiziert sie im JSON-Format.
* **Python AI-Backend:** Empfängt MQTT-Nachrichten, formatiert die Daten (Temperatur, Luftfeuchtigkeit, Licht) und leitet sie an ein trainiertes Random-Forest-Modell weiter.
* **Bidirektionale Kommunikation:** Das Backend sendet basierend auf der KI-Vorhersage Steuerungsbefehle (LED ON/OFF) an den ESP32 zurück.

## Tech-Stack & Hardware
**Hardware:**
* Wemos D1 Mini32 (ESP32)
* RGB LED (Pin 18, 19, 26)

**Software:**
* **C++ / PlatformIO:** Für die ESP32-Firmware (Bibliotheken: PubSubClient, ArduinoJson / nlohmann::json).
* **Python 3:** Für das Backend (Bibliotheken: `paho-mqtt`, `pandas`, `scikit-learn`).
* **Mosquitto:** Als lokaler MQTT-Broker.

---

## Setup & Installation

### 1. MQTT Broker (Mosquitto)
Ein lokaler Mosquitto-Broker muss laufen und anonyme Verbindungen auf Port 1883 zulassen (`allow_anonymous true`). Die Firewall muss Port 1883 für das lokale Netzwerk freigeben.

### 2. ESP32 (PlatformIO)
Damit der C++ Code kompiliert werden kann, müssen die WLAN- und MQTT-Daten lokal hinterlegt werden.

1. Erstelle im Ordner `espSensorDataMqtt/IIoT_Predictive_Maintenance/include/` eine Datei namens `secrets.h`.
2. Füge folgenden Code ein und passe deine Daten an:

```cpp
#pragma once
#define SECRET_WIFI_SSID "Dein_WLAN_Name"
#define SECRET_WIFI_PASS "Dein_WLAN_Passwort"
#define SECRET_MQTT_BROKER "IP" // IP des PCs mit dem Mosquitto Broker

```

3. Flashe den Code über PlatformIO auf den ESP32. Lade vorher das SPIFFS-Dateisystem mit der `data.csv` hoch.

### 3. Python Backend

Navigiere in den Python-Ordner und installiere die benötigten Bibliotheken:

```bash
pip install paho-mqtt pandas scikit-learn

```

Starte das Backend, um auf Daten des ESP32 zu lauschen:

```bash
python backend.py

```

## 📡 MQTT Topics

* `plant/sensors`: ESP32 publiziert Sensordaten im JSON-Format.
* `led/control`: Python-Backend publiziert Steuerungsbefehle (`{"LED": "ON"}` oder `{"LED": "OFF"}`).

```
