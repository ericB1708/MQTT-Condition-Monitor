#include "MqttReceiveHelper.h"
#include <nlohmann/json.hpp>
#include <globals.h>
#include <Arduino.h>

using json = nlohmann::json;

void onMessageReceive(char *topic, byte *payload, unsigned int length)
{
    Serial.println("Message arrive in Topic : ");
    Serial.println(topic);

    if (String(topic) == "led/control")
    {
        std::string message(reinterpret_cast<const char *>(payload), length);
        try
        {
            json j = json::parse(message);

            std::string ledStatus = j["LED"];

            if (ledStatus == "ON")
            {
                Serial.println("LED ON");
                led.ledRed();
            }
            else if (ledStatus == "OFF")
            {
                Serial.println("LED OFF");
                led.ledGreen();
            }
        }
        catch (const std::exception &e)
        {
            Serial.println("Error on json parse");
        }
    }
}