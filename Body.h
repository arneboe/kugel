#pragma once
#define BODY_PIN 7
#define BODY_COLOR_ORDER RGB
#define BODY_LEDS    112 //FIXME das sind keine 130

//Return reference to the pixel at (x,y)
CRGB& getBodyPixel(const uint8_t x, const uint8_t y);
//set all leds to black
void clearBodyPixels();

//function pointers for effect methods
typedef void (*BodyUpdatePtr)(const uint16_t, const uint16_t, const uint8_t, const uint8_t);
typedef void (*BodyInitPtr)(const uint8_t, const uint8_t);

CRGB bodyLeds[BODY_LEDS];

//available effects
enum BodyMode
{
    BODY_TEST_MODE,
    //insert new modes above NUM_MODES
    NUM_BODY_MODES
};

BodyUpdatePtr bodyExecute[NUM_BODY_MODES];
BodyInitPtr bodyInitialize[NUM_BODY_MODES];
BodyMode currentBodyMode = BODY_TEST_MODE;
BodyMode lastBodyMode = currentBodyMode;


#define BODY_W 16 //TODO
#define BODY_H 7 //TODO

#include "BodyTestMode.h"

void bodySetup()
{
  FastLED.addLeds<LED_TYPE, BODY_PIN, BODY_COLOR_ORDER>(bodyLeds, BODY_LEDS).setCorrection(TypicalLEDStrip);
  bodyExecute[BODY_TEST_MODE] = updateBody;
  bodyInitialize[BODY_TEST_MODE] = initBodyTest;

  bodyInitialize[currentBodyMode](BODY_W, BODY_H); 
}

void bodyLoop(const uint16_t timeSinceLastCall, const uint16_t speed)
{
  if(currentBodyMode != lastBodyMode)
  {
    lastBodyMode = currentBodyMode;
    bodyInitialize[currentBodyMode](BODY_W, BODY_H);    
  }
  
  bodyExecute[currentBodyMode](timeSinceLastCall, speed, BODY_H, BODY_W); //FIXME do not hardcode numRows and numColls
}


//16 x 7
//[y] [y]
uint8_t bodyMapping[7][16] = {{0, 1,2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12,13, 14, 15},
                             {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 16},
                             {34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 32, 33},
                             {51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 48, 49, 50},
                             {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 64, 65, 66, 67},
                             {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 80, 81, 82, 83, 84},
                             {102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 96, 97, 98, 99, 100, 101}};

CRGB& getBodyPixel(const uint8_t x, const uint8_t y)
{ 
  return bodyLeds[bodyMapping[y][x]];
}

void clearBodyPixels()
{
  for(int i = 0; i < BODY_LEDS; ++i)
  {
    bodyLeds[i] = CRGB::Black;
  }
}






