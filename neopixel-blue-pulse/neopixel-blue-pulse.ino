// Simple NeoPixel test.  Lights just a few pixels at a time so a
// long strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip -- look for the data
// direction arrows printed on the strip.

#include <Adafruit_NeoPixel.h>

#define PIN    6
#define N_LEDS 300 // 10 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  chase(0x33F6FF); // Lighter blue
  chase(0x33B5FF);
  chase(0x33DDFF);
  chase(0x33D1FF);
  chase(0x33CAFF);
  chase(0x33C1FF);
  chase(0x3341FF);
  chase(0x334EFF);
  chase(0x3351FF);
  chase(0x336EFF); // Darker blue
}

static void chase(uint32_t c) {
  uint16_t pixels_to_light = 25;
  uint16_t bands = 5;
  uint16_t band_length = floor(strip.numPixels()/bands);
  for(uint16_t i=0; i<band_length; i++) {
      for(uint16_t b=0; b<bands; b++) {
          strip.setPixelColor(i+(b*band_length), c);                  // Draw new pixel
          strip.setPixelColor(i+(b*band_length)-pixels_to_light, 0);  // Erase pixel a few steps back
      }
      
      // Erase the last pixels on the strip from the previous run
      if (i<=pixels_to_light) {
          strip.setPixelColor(strip.numPixels()-1-pixels_to_light+i, 0);
      }
      
      strip.show();
      delay(35);
  }
}
