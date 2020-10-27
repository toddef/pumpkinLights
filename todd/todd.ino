#include <FastLED.h>
  
#include "Constants.h"

CRGB leds[NUM_LEDS];

const CRGB LEDS_STARTING_COLORS[NUM_LEDS] = {
// Frankenstirn
   CRGB::Green
  ,CRGB::DarkGreen 
// Mummy  
  ,CRGB::Gold
  ,CRGB::Yellow
// Dracula  
  ,CRGB::Red
  ,CRGB::DarkRed
// reaper head  
  ,CRGB::Orange
  ,CRGB::DarkOrange
// halooween pumpkin  
  ,CRGB::Orange
  ,CRGB::DarkOrange
// mike myers  
  ,CRGB::Orange
  ,CRGB::DarkOrange
// mike mysers 2  
  ,CRGB::Orange
  ,CRGB::DarkOrange
// witch
  ,CRGB::Green
  ,CRGB::DarkGreen
// pumpkin
  ,CRGB::Orange
  ,CRGB::DarkOrange
// skeleton
  ,CRGB::White
  ,CRGB::White
  
};

int brightnessForFade[NUM_LEDS];
int fadeAmount[NUM_LEDS];

void setup() {
  delay(3000); // sanity delay
  
  randomSeed(analogRead(0));
  
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );
  
  fill_rainbow( leds, NUM_LEDS, 0, 40);
  FastLED.show(); // display this frame

  delay(3000); // sanity delay

  for(int i =0; i < NUM_LEDS; i++)
  {
    leds[i] = LEDS_STARTING_COLORS[i];
    brightnessForFade[i] = BRIGHT_START;
    fadeAmount[i] = 1;
  }  
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  random16_add_entropy( random());
  
  fade();
  
  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void fade()
{  
   for(int i = 0; i < NUM_LEDS; i++ )
   {
      leds[i] = LEDS_STARTING_COLORS[i];  // Reset the LED to the starting color

      // Check for flicker. On a Flicker randomly increase or decrease the brightness fade 
      if (random(100) < FLICKER_CHANCE)
      {
        if (random(2)){
          fadeAmount[i] = -fadeAmount[i];  
        }     
        brightnessForFade[i] = brightnessForFade[i] + (fadeAmount[i] * random(FLICKER_RANGE_LOW,FLICKER_RANGE_HIGH));
      }

     // Check to continue the gradual fade up or down of the LED
      if (random(100) < FADE_CHANCE){
        brightnessForFade[i] = brightnessForFade[i] + (fadeAmount[i] * random(1,2));

        // Reverse fade direction once we reach the boundaries
        if(brightnessForFade[i] < BRIGHT_START || brightnessForFade[i] > BRIGHT_END)
        {
          fadeAmount[i] = -fadeAmount[i]; 
        }           
      }
      
      // Constraing the calculated brightness to the limits
      brightnessForFade[i] = constrain(brightnessForFade[i], BRIGHT_START, BRIGHT_END);
      
      leds[i].fadeLightBy(brightnessForFade[i]);
   }
}
