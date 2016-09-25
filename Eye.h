#pragma once
#define LEFT_EYE_PIN 2
#define RIGHT_EYE_PIN 9
#define EYE_COLOR_ORDER RGB
#define LEFT_EYE_LEDS 48 
#define RIGHT_EYE_LEDS 51
#define EYE_W 18
#define EYE_H 5

//Return reference to the pixel at (x,y)
CRGB& getEyePixel(const uint8_t x, const uint8_t y, bool left);
//set all leds to black
void clearEyePixels();

//function pointers for effect methods
typedef void (*EyeUpdatePtr)(const uint16_t, const uint16_t, const uint8_t, const uint8_t);
typedef void (*EyeInitPtr)(const uint8_t, const uint8_t);


CRGB leftEyeLeds[LEFT_EYE_LEDS];
CRGB rightEyeLeds[RIGHT_EYE_LEDS];

//available effects
enum EyeMode
{   EYE_TEST_MODE,
    EYE_RED,
    EYE_GREEN,
    EYE_BLUE,
    EYE_YELLOW,
    EYE_CYAN,
    EYE_MAGENTA,
    EYE_FADE,
    EYE_FADE2,
    EYE_FIRE,
    //insert new modes above NUM_MODES
    NUM_EYE_MODES
};

EyeUpdatePtr eyeExecute[NUM_EYE_MODES];
EyeInitPtr eyeInitialize[NUM_EYE_MODES];
EyeMode currentEyeMode = EYE_TEST_MODE;
EyeMode lastEyeMode = currentEyeMode;

#include "EyeTestMode.h"
#include "EyeStatic.h"
#include "EyeFade.h"

void eyeSetup()
{
  FastLED.addLeds<LED_TYPE, LEFT_EYE_PIN, EYE_COLOR_ORDER>(leftEyeLeds, LEFT_EYE_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, RIGHT_EYE_PIN, EYE_COLOR_ORDER>(rightEyeLeds, RIGHT_EYE_LEDS).setCorrection(TypicalLEDStrip);
  
  eyeExecute[EYE_TEST_MODE] = updateEyeTest;
  eyeInitialize[EYE_TEST_MODE] = initEyeTest;

  eyeExecute[EYE_RED] = updateEyeStatic;
  eyeInitialize[EYE_RED] = initEyeStaticColor;

  eyeExecute[EYE_GREEN] = updateEyeStatic;
  eyeInitialize[EYE_GREEN] = initEyeStaticColor;

  eyeExecute[EYE_BLUE] = updateEyeStatic;
  eyeInitialize[EYE_BLUE] = initEyeStaticColor;

  eyeExecute[EYE_YELLOW] = updateEyeStatic;
  eyeInitialize[EYE_YELLOW] = initEyeStaticColor;

  eyeExecute[EYE_CYAN] = updateEyeStatic;
  eyeInitialize[EYE_CYAN] = initEyeStaticColor;

  eyeExecute[EYE_MAGENTA] = updateEyeStatic;
  eyeInitialize[EYE_MAGENTA] = initEyeStaticColor;

  eyeExecute[EYE_FADE] = updateEyeFade;
  eyeInitialize[EYE_FADE] = initEyeFade;

  eyeExecute[EYE_FADE2] = updateEyeFade2;
  eyeInitialize[EYE_FADE2] = initEyeFade;

  eyeInitialize[currentEyeMode](EYE_H, EYE_W);
}

void eyeLoop(const uint16_t timeSinceLastCall, const uint16_t speed)
{
  const int val = analogRead(A2);
  currentEyeMode = (EyeMode)map(val, 0, 1024, 0, NUM_EYE_MODES);

  if(currentEyeMode == EYE_FIRE)
    currentEyeMode = EYE_RED;
  
  if(currentEyeMode != lastEyeMode)
  {
    lastEyeMode = currentEyeMode;
    eyeInitialize[currentEyeMode](EYE_H, EYE_W);
  }
  eyeExecute[currentEyeMode](timeSinceLastCall, speed, EYE_H, EYE_W);
}


// [y][x]
uint8_t leftMapping[5][18] = {{47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
                              {41, 41, 46, 46, 46, 45, 45, 45, 44, 44, 44, 44, 43, 43, 43, 42, 42, 42},
                              {40, 40, 30, 31, 31, 32, 32, 33, 34, 35, 35, 35, 36, 37, 37, 38, 38, 39},
                              {27, 28, 29, 16, 16, 17, 18, 19, 20, 21, 21, 21, 22, 23, 24, 25, 25, 26},
                              {12, 13, 14, 15, 15,  0,  1,  2,  3,  4,  5, 5,  6,  7,  8,  9, 10, 11}};

uint8_t rightMapping[5][18] = {{50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
                               {45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 49, 49, 44, 44, 44, 44, 45},
                               {35, 36, 36, 37, 37, 38, 38, 39, 40, 41, 41, 41, 47, 43, 43, 33, 34, 34},
                               {19, 20, 21, 22, 22, 23, 24, 25, 26, 27, 28, 28, 29, 30, 31, 32, 18, 18},
                               {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17}};

CRGB& getEyePixel(const uint8_t x, const uint8_t y, bool left)
{  
  if(left)
    return leftEyeLeds[leftMapping[y][x]];
  return rightEyeLeds[rightMapping[y][x]]; 
}

void clearEyePixels()
{
  for(int i = 0; i < LEFT_EYE_LEDS; ++i)
  {
    leftEyeLeds[i] = CRGB::Black;
  }
  
  for(int i = 0; i < RIGHT_EYE_LEDS; ++i)
  {
    rightEyeLeds[i] = CRGB::Black;
  }
}






