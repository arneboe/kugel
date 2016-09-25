#include "Wait.h"

struct 
{;
 uint32_t timePassed; //in us
 uint8_t offset;
} bodyFireState;


void initBodyFire(const uint8_t numRows,
                 const uint8_t numColls)
{
  bodyFireState.timePassed = 0;
}

void updateBodyFire(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{  
  WAIT(map(speed, 0, 1023, 0, 600000), bodyTestState.timePassed, timeSinceLastCall);
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      const int xOff = (x + bodyFireState.offset) % numColls;
      const int yOff = (y + bodyFireState.offset) % numRows;
      const int dist = xOff * xOff + yOff * yOff;
      const int maxDist = numRows * numRows + numColls * numColls;
      const int h = map(dist, 0, maxDist, 0, 40);
      CRGB& p = getBodyPixel(x, y);
      p.setHue(h);
    }
  }
  ++bodyFireState.offset;
}




