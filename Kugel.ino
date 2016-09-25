#include <FastLED.h>
#define LED_TYPE    WS2811

uint16_t getTimeSinceLastCall();

#include "Body.h"
#include "Eye.h"

void setup() {
  Serial.begin(9600);
  
  bodySetup();
  eyeSetup();
  //TODO other setups here
}


unsigned long lastStroboOnTime = 0;
unsigned long lastStroboOffTime = 0;
bool stroboOn = false;


void loop() {
  const uint16_t speed = analogRead(A0);
  Serial.print(speed); Serial.print("  ");
 const uint8_t brightness = map(analogRead(A3), 0, 1023, 0, 255);
 Serial.print(brightness); Serial.print("  ");
 const uint16_t strobo = analogRead(A5);
 Serial.print(strobo); Serial.print("  ");
 Serial.println("");
 const uint16_t timeSinceLastCall = getTimeSinceLastCall();
 
 bodyLoop(timeSinceLastCall, speed);
 eyeLoop(timeSinceLastCall, speed);


 
 if(strobo < 990)
 {
    const unsigned long time = micros();
    const unsigned long offTime = map(strobo, 0, 1023, 4000, 100000);
    if(stroboOn && time - lastStroboOnTime > 12000)
    {
      FastLED.setBrightness(0);
      stroboOn = false;
      lastStroboOffTime = time;
    }
    else if(!stroboOn && time - lastStroboOffTime > offTime)
    {
      FastLED.setBrightness(brightness);
      stroboOn = true;
      lastStroboOnTime = time;
    }
 }
 else
 {
    stroboOn = false;
    FastLED.setBrightness(brightness);
 }
 
 
 FastLED.show(); 
}

/*


CRGB& getPixel(const uint8_t x, const uint8_t y)
{
  return leds[mapping[y][x]];
}

void clearPixels()
{
  FastLED.clear();
}
*/

uint16_t getTimeSinceLastCall()
{
  static unsigned long lastTime = 0;
  const unsigned long currentTime = micros();
  const uint16_t diff = currentTime - lastTime;
  lastTime = currentTime;
  return diff;
}

