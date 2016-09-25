#include "Wait.h"

struct 
{
 uint8_t h;
 uint32_t timePassed; //in us
} eyeFadeState;


void initEyeFade(const uint8_t numRows,
                 const uint8_t numColls)
{
  eyeFadeState.timePassed = 0;
}

void updateEyeFade(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{  
  WAIT(map(speed, 0, 1023, 0, 600000), eyeFadeState.timePassed, timeSinceLastCall);
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getEyePixel(x, y, true);
      p.setHue(eyeFadeState.h);
      CRGB& p2 = getEyePixel(x, y, false);
      p2.setHue(eyeFadeState.h + 30);
    }
  }
  eyeFadeState.h += 2;
}

void updateEyeFade2(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{  
  WAIT(map(speed, 0, 1023, 0, 600000), eyeFadeState.timePassed, timeSinceLastCall);
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getEyePixel(x, y, true);
      p.setHue(eyeFadeState.h);
      CRGB& p2 = getEyePixel(x, y, false);
      p2.setHue(eyeFadeState.h + 30);
    }
  }
  eyeFadeState.h += 120;
}



