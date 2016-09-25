#pragma once
#include "Wait.h"

struct
{
  uint8_t offset;
  uint32_t timePassed; //in us
  int hStep;
  uint8_t h;
} eyeTestState;


void initEyeTest(const uint8_t numRows, const uint8_t numColls)
{
  Serial.println("init");
  eyeTestState.offset = 5;
  eyeTestState.h = 0;
  eyeTestState.timePassed = 300000; //some big number to force execution on first call
  eyeTestState.hStep = 255 / numRows;
}


void updateEyeTest(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{        
   WAIT(map(speed, 0, 1023, 0, 600000), bodyTestState.timePassed, timeSinceLastCall);
 
  clearEyePixels();
  uint32_t end = eyeTestState.offset + 3;

  for(uint32_t x = eyeTestState.offset; x < end; ++x)
  { 
    const uint8_t realX = x % numColls;
    for(int y = 0; y < numRows; ++y)
    {
        CRGB& left = getEyePixel(realX, y, true);
        CRGB& right = getEyePixel(realX, y, false);
        right.setHue(eyeTestState.h);
        left.setHue(eyeTestState.h);
    }
  }
  
  
  ++eyeTestState.offset;
  ++eyeTestState.h;
}


