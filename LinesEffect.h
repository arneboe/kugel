#pragma once
#include "Wait.h"
struct
{
  uint8_t row;
  int8_t dir;
  uint32_t timePassed; //in us
} linesState;


void initLines(const uint8_t numRows,
                 const uint8_t numColls)
{
  linesState.row = 0;
  linesState.dir = 1;
  linesState.timePassed = 300000; //some big number to force execution on first call
}

/** @param timeSinceLastCall in micro seconds
 *  @param speed Speed factor chosen by the user. range: [0 .. 255] [slow .. fast]*/
void updateLines(const uint16_t timeSinceLastCall, const uint8_t speed, const uint8_t numRows,
                 const uint8_t numColls)
{
  //TODO use speed
  WAIT(80000, linesState.timePassed, timeSinceLastCall);
  
  if(linesState.row >= numRows - 1)
  {
    linesState.dir = -1;
  }
  else if(linesState.row == 0)
  {
    linesState.dir = 1;
  }
  linesState.row += linesState.dir;

  clearPixels();

  for(int x = 0; x < numColls; ++x)
  { 
    CRGB& pixel = getPixel(x, linesState.row);
    pixel.r = 0;
    pixel.g = 255;
    pixel.b = 0;
  }
}


