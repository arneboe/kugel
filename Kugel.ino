#include <FastLED.h>

//FastLED Settings
#define DATA_PIN    A0
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    48

//Return reference to the pixel at (x,y)
CRGB& getPixel(const uint8_t x, const uint8_t y);

//set all leds to black
void clearPixels();

uint16_t getTimeSinceLastCall();

//effects need to be included after FastLED.h to get access to the CRGB type
//and after the getPixel prototype to be able to use getPixel
#include "LinesEffect.h"


//function pointers for effect methods
typedef void (*UpdatePtr)(const uint16_t, const uint8_t, const uint8_t, const uint8_t);
typedef void (*InitPtr)(void);

//available effects
enum Mode
{
    LINES,
    //insert new modes above NUM_MODES
    NUM_MODES
};

//globals
//mode management
UpdatePtr execute[NUM_MODES];
InitPtr initialize[NUM_MODES];
Mode currentMode = LINES;
Mode lastMode = currentMode;

CRGB leds[NUM_LEDS];


void setup() {
  
  currentMode = LINES;
  lastMode = currentMode;

  execute[LINES] = updateLines;
  initialize[LINES] = initLines;

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  Serial.begin(9600);
}



void loop() {
  const uint8_t speed = 100; //TODO read from user
  const uint8_t brightness = 255; //TODO read from user 
  currentMode = LINES; //TODO read from user

  if(currentMode != lastMode)
  {
    lastMode = currentMode;
    initialize[currentMode]();    
  }
  const uint16_t timeSinceLastCall = getTimeSinceLastCall();
  execute[currentMode](timeSinceLastCall, speed, 5, 16); //FIXME do not hardcode numRows and numColls
  FastLED.setBrightness(brightness);
  FastLED.show(); 
}

CRGB& getPixel(const uint8_t x, const uint8_t y)
{
  // [y][x]
  static uint8_t mapping[5][16] = {{47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
                                   {41, 41, 46, 46, 49, 45, 45, 44, 44, 44, 43, 43, 43, 42, 42, 42},
                                   {40, 40, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39},
                                   {27, 28, 29, 16, 17, 18, 19, 20, 21, 21, 22, 23, 24, 25, 25, 26},
                                   {12, 13, 14, 15,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}};
  return leds[mapping[y][x]];
}

void clearPixels()
{
  FastLED.clear();
}

uint16_t getTimeSinceLastCall()
{
  static unsigned long lastTime = 0;
  const unsigned long currentTime = micros();
  const uint16_t diff = currentTime - lastTime;
  lastTime = currentTime;
  return diff;
}


