#include <FastLED.h>
#include "led.h"

CRGB leds[NUM_LEDS];

void setup_LED() {

  for(int i = 0; i < NUM_LEDS; ++i){
    leds[i] = CRGB::Black;
  }

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(4);

}

void display_LED(int height) {

  int li = floor(height);
  li = NUM_LEDS - li;  //upside down

  if(li > 0) {
    leds[li-1] = CRGB::Red;
  }
  leds[li] = CRGB::Red;
  if(li < NUM_LEDS-1) {
    leds[li+1] = CRGB::Red;
  }

  FastLED.show();
  
  if(li > 0) {
      leds[li-1] = CRGB::Black;
  }
  
  leds[li] = CRGB::Black;
  if(li < NUM_LEDS-1) {
      leds[li+1] = CRGB::Black;
  }

} 