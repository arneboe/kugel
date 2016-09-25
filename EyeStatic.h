

void initEyeStaticColor(const uint8_t numRows,
                 const uint8_t numColls) {}

void updateEyeStatic(const uint16_t timeSinceLastCall, const uint16_t speed, const uint8_t numRows,
                const uint8_t numColls)
{
  CRGB col = CRGB::Red;

  switch(currentBodyMode)
  {
    case EYE_RED: col = CRGB::Red; break;
    case EYE_GREEN: col = CRGB::Green; break;
    case EYE_BLUE: col = CRGB::Blue; break;
    case EYE_YELLOW: col = CRGB::Yellow; break;
    case EYE_CYAN: col = CRGB::Cyan; break;
    case EYE_MAGENTA: col = CRGB::Magenta; break;
  }
  
  for(int x = 0; x < numColls; ++x)
  {
    for(int y = 0; y < numRows; ++y)
    {
      CRGB& p = getEyePixel(x, y, true);
      CRGB& p2 = getEyePixel(x, y, false);
      p = col;
      p2 = col;
    }
  }
}

