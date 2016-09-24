#pragma once
#include "Wait.h"

struct 
{
 int col;
 uint32_t timePassed; //in us
} bodyTestState;

void initBodyTest(const uint8_t numRows,
                 const uint8_t numColls)
{
  bodyTestState.col = 0;
}


void updateBody(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{
  WAIT(map(speed, 0, 1023, 0, 600000), bodyTestState.timePassed, timeSinceLastCall);
  
  clearBodyPixels();
  
  for(uint8_t y = 0; y < numColls; ++y)
  {
    CRGB& p = getBodyPixel(bodyTestState.col, y);
    p.setHue(0);
  }
  
 // bodyTestState.col = (bodyTestState.col + 1) % numColls;
}


