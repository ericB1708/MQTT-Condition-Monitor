#include "WifiConnection.h"
#include <Arduino.h>

void WifiConnection::setSsidAndPassword(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}

WifiConnection::WifiConnection(char *ssid, char *password)
{
    this->ssid = ssid;
    this->password = password;
}

WifiConnection::~WifiConnection()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.disconnect();
    }
}

void WifiConnection::ConnectToWifi()
{
    WiFi.begin(this->ssid, this->password);
    Serial.println("Connecting...");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }
    Serial.println("Connected");
}