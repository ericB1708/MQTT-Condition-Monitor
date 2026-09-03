#include "LedControl.h"
#include <Arduino.h>

LedControl::LedControl(int redPin, int bluePin, int greenPin)
{
    this->redPin = redPin;
    this->bluePin = bluePin;
    this->greenPin = greenPin;
}

LedControl::~LedControl()
{
}

void LedControl::setupLed()
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void LedControl::ledRed()
{
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, HIGH);
}

void LedControl::ledGreen()
{
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
}
