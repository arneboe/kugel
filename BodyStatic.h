

void initBodyStaticColor(const uint8_t numRows,
                 const uint8_t numColls) {}

void updateBodyStatic(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{
  CRGB col = CRGB::Red;

  switch(currentBodyMode)
  {
    case BODY_RED: col = CRGB::Red; break;
    case BODY_GREEN: col = CRGB::Green; break;
    case BODY_BLUE: col = CRGB::Blue; break;
    case BODY_YELLOW: col = CRGB::Yellow; break;
    case BODY_CYAN: col = CRGB::Cyan; break;
    case BODY_MAGENTA: col = CRGB::Magenta; break;
  }
  
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getBodyPixel(x, y);
      p = col;
    }
  }
}

