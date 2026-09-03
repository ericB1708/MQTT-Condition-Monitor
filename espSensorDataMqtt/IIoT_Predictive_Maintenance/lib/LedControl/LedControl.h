#pragma once

class LedControl
{
private:
    /* data */
    int redPin;
    int bluePin;
    int greenPin;

public:
    LedControl(int redPin, int bluePin, int greenPin);
    ~LedControl();
    void setupLed();
    void ledRed();
    void ledGreen();
};