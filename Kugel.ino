#include <FastLED.h>

//FastLED Settings
#define DATA_PIN    7
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    48

//Return reference to the pixel at (x,y)
CRGB& getPixel(const uint8_t x, const uint8_t y);
CRGB& getBuffer(const uint8_t x, const uint8_t y);

//set all leds to black
void clearPixels();

void clearBuffer();

uint16_t getTimeSinceLastCall();



//function pointers for effect methods
typedef void (*UpdatePtr)(const uint16_t, const uint8_t, const uint8_t, const uint8_t);
typedef void (*InitPtr)(const uint8_t, const uint8_t);


//available effects
enum Mode
{
    LINES,
    VORTEX,
    VORTEX2,
    //insert new modes above NUM_MODES
    NUM_MODES
};

//globals
//mode management
UpdatePtr execute[NUM_MODES];
InitPtr initialize[NUM_MODES];
Mode currentMode = VORTEX;
Mode lastMode = currentMode;


//effects need to be included here to have access to some of the globals
#include "LinesEffect.h"
#include "VortexEffect.h"


CRGB leds[NUM_LEDS];
CRGB buffer[NUM_LEDS];


void setup() {
  
  currentMode = VORTEX2;
  lastMode = currentMode;

  
  execute[LINES] = updateLines;
  initialize[LINES] = initLines;
  
  execute[VORTEX] = updateVortex;
  initialize[VORTEX] = initVortex;
  execute[VORTEX2] = updateVortex;
  initialize[VORTEX2] = initVortex;

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  Serial.begin(9600);
  initialize[currentMode](5, 16); 
}



void loop() {
  const uint8_t speed = 100; //TODO read from user
  const uint8_t brightness = 255; //TODO read from user 
 // currentMode = VORTEX; //TODO read from user

  if(currentMode != lastMode)
  {
    lastMode = currentMode;
    initialize[currentMode](5, 16);    
  }
  const uint16_t timeSinceLastCall = getTimeSinceLastCall();
  execute[currentMode](timeSinceLastCall, speed, 5, 16); //FIXME do not hardcode numRows and numColls
  FastLED.setBrightness(brightness);
  FastLED.show(); 
}


// [y][x]
uint8_t mapping[5][16] = {{47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
                          {41, 41, 46, 46, 49, 45, 45, 44, 44, 44, 43, 43, 43, 42, 42, 42},
                          {40, 40, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39},
                          {27, 28, 29, 16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 25, 26},
                          {12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}};

CRGB& getPixel(const uint8_t x, const uint8_t y)
{
  return leds[mapping[y][x]];
}
CRGB& getBuffer(const uint8_t x, const uint8_t y)
{
  return buffer[mapping[y][x]];
}

void clearPixels()
{
  FastLED.clear();
}

void clearBuffer()
{
  for (int i = 0; i < NUM_LEDS; ++i)
  {
    buffer[i] = CRGB::Black;
  }
}

uint16_t getTimeSinceLastCall()
{
  static unsigned long lastTime = 0;
  const unsigned long currentTime = micros();
  const uint16_t diff = currentTime - lastTime;
  lastTime = currentTime;
  return diff;
}

