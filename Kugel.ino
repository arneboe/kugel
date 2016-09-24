#include <FastLED.h>
#define LED_TYPE    WS2811

uint16_t getTimeSinceLastCall();

#include "Body.h"

void setup() {
  Serial.begin(9600);
  
  bodySetup();
  //TODO other setups here
}


void loop() {
  const uint16_t speed = analogRead(A0);; //TODO read from user
  const uint8_t brightness = 255; //TODO read from user 
 // currentMode = VORTEX; //TODO read from user
 const uint16_t timeSinceLastCall = getTimeSinceLastCall();
 
 bodyLoop(timeSinceLastCall, speed);
 //TODO other loops here
 
 FastLED.setBrightness(brightness);
 FastLED.show(); 
}

/*
// [y][x]
uint8_t mapping[5][16] = {{47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
                          {41, 41, 46, 46, 49, 45, 45, 44, 44, 44, 43, 43, 43, 42, 42, 42},
                          {40, 40, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39},
                          {27, 28, 29, 16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 25, 26},
                          {12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}};

CRGB& getPixel(const uint8_t x, const uint8_t y)
{
  return leds[mapping[y][x]];
}

void clearPixels()
{
  FastLED.clear();
}
*/

uint16_t getTimeSinceLastCall()
{
  static unsigned long lastTime = 0;
  const unsigned long currentTime = micros();
  const uint16_t diff = currentTime - lastTime;
  lastTime = currentTime;
  return diff;
}

