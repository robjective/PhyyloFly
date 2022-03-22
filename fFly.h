/*
fFly.h A library for simulating fireflies
Created by Rob Goldman, Decemeber 2017
Released into the public domain.
*/

#ifndef fFly_h
#define fFly_h
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"


class Fly
{
    public:
    // Functions
    Fly();
    Fly(uint32_t flyColor, uint32_t blinkColor, long blinkLength, long onRate);
    void Update();
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    void setFgColor(uint32_t sColor);
    void setBgColor(uint32_t sColor);

    float LFO(int seed);
    uint32_t startColor;
        
    // Variables
    int ledState; // -1 off, 0 transitioning, 1 on
    long startMillis, blinkLength,onRate;
    uint32_t flyColor;
    uint32_t blinkColor;
    float rdiff, bdiff, gdiff; 
    
    private:
    int _increment;
};


#endif
