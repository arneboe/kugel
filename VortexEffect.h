#pragma once
#include "Wait.h"
struct
{
  uint8_t offset;
  uint32_t timePassed; //in us
  int hStep;
  uint8_t h;
} vortexState;

void initVortex(const uint8_t numRows,
                 const uint8_t numColls)
{
  vortexState.offset = 5;
  vortexState.h = 0;
  vortexState.timePassed = 300000; //some big number to force execution on first call
  vortexState.hStep = 255 / numColls;
}

void updateVortex(const uint16_t timeSinceLastCall, const uint8_t speed, const uint8_t numRows,
                 const uint8_t numColls)
{
  //TODO use speed
  WAIT(20000, vortexState.timePassed, timeSinceLastCall);
  
  clearPixels();

  uint32_t end = vortexState.offset + numColls; //for VORTEX
  if(currentMode == VORTEX)
  {
    vortexState.h = 0;
  }
  else if(currentMode == VORTEX2)
  {
    end = vortexState.offset + 3;  
  }
  for(uint32_t x = vortexState.offset; x < end; ++x)
  { 
    const uint8_t realX = x % numColls;
    for(int y = 0; y < numRows; ++y)
    {
        CRGB& pixel = getPixel(realX, y);
        pixel.setHue(vortexState.h);
    }
    if(currentMode == VORTEX)
    {
      vortexState.h += vortexState.hStep;
    }
  }
  ++vortexState.offset;
  if(currentMode == VORTEX2)
  {
    ++vortexState.h;
  }
}
                  

