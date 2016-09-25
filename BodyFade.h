#include "Wait.h"

struct 
{
 uint8_t h;
 uint32_t timePassed; //in us
} bodyFadeState;


void initBodyFade(const uint8_t numRows,
                 const uint8_t numColls)
{
  bodyFadeState.timePassed = 0;
}

void updateBodyFade(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{  
  WAIT(map(speed, 0, 1023, 0, 600000), bodyTestState.timePassed, timeSinceLastCall);
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getBodyPixel(x, y);
      p.setHue(bodyFadeState.h);
    }
  }
  bodyFadeState.h += 2;
}

void updateBodyFade2(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{  
  WAIT(map(speed, 0, 1023, 0, 600000), bodyTestState.timePassed, timeSinceLastCall);
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getBodyPixel(x, y);
      p.setHue(bodyFadeState.h);
    }
  }
  bodyFadeState.h += 120;
}



