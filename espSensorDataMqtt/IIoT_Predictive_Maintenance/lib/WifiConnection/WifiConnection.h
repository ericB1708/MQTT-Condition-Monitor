#pragma once
#include <WiFi.h>

class WifiConnection
{
private:
    /* data */
    char *ssid;
    char *password;

public:
    WifiConnection(char *ssid, char *password);
    ~WifiConnection();

    void setSsidAndPassword(char *ssid, char *password);

    void ConnectToWifi();
};
