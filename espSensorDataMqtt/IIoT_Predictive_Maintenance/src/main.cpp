#include <Arduino.h>
#include <CsvReader.h>
#include <SPIFFS.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WifiConnection.h>
#include <MqttReceiveHelper.h>
#include <string>
#include <nlohmann/json.hpp>
#include <LedControl.h>
#include <globals.h>
#include <secrets.h>

using json = nlohmann::json;

// led
LedControl led(19, 18, 26);

// global value
SensorDatas globalSensorDatas;

// Wifi Data
char ssid[] = SECRET_WIFI_SSID;
char password[] = SECRET_WIFI_PASS;
WifiConnection wifi(ssid, password);

// MQTT Broker
const char *mqtt_broker = SECRET_MQTT_BROKER;
const char *SubTopic = "led/control";
const char *PubTopic = "plant/sensors";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

// put function declarations here:
std::string getDictToString(std::map<std::string, int> datadict);
void publishData(std::string data);

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);

  // LED Config
  led.setupLed();

  // connect to Wifi
  wifi.ConnectToWifi();

  // mqtt
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(onMessageReceive);

  while (!client.connected())
  {
    Serial.print("Connect with MQTT Broker...");
    if (client.connect("Esp32_Plant"))
    {
      Serial.println(" connected");
      client.subscribe(SubTopic);
    }
    else
    {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe(SubTopic);

  if (!SPIFFS.begin(true))
  {
    Serial.println("Fehler beim Mounten von SPIFFS");
    return;
  }
  globalSensorDatas = readCsvData();
}

const unsigned long durationMs = 3000;
unsigned long previousMillis = 0;
bool waiting = false;

void loop()
{

  unsigned long currentMillis = millis();

  if (waiting && (currentMillis - previousMillis >= durationMs))
  {
    waiting = false;
    auto data = globalSensorDatas.getOneSensorData();
    std::string jsonData = getDictToString(data);
    publishData(jsonData);
  }
  else if (!waiting)
  {
    previousMillis = currentMillis;
    waiting = true;
  }

  client.loop();
}

// put function definitions here:
void publishData(std::string data)
{
  client.publish(PubTopic, data.c_str());
  Serial.println("Data should send");
}

std::string getDictToString(std::map<std::string, int> datadict)
{
  json j;
  for (const auto &pair : datadict)
  {
    j[pair.first] = pair.second;
  }
  std::string jsonString = j.dump();
  return jsonString;
}
