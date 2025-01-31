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

#define PIN    0
#define N_LEDS 150     // 5 meter reel @ 30 LEDs/m                                                                                                                                                              // 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  chase(0xFFFFFF); // White
  chase(0xFF0000); // Red
  chase(0x00FF00); // Green
  chase(0x0000FF); // Blue
}

static void chase(uint32_t c) {
  uint16_t pixels_to_light = 6;
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i  , c);                // Draw new pixel
      strip.setPixelColor(i-pixels_to_light, 0);  // Erase pixel a few steps back
      strip.show();
      delay(10);
  }
  for(uint16_t i=strip.numPixels() - 1; i > 0; i--) {
      strip.setPixelColor(i  , c);                // Draw new pixel
      strip.setPixelColor(i+pixels_to_light, 0);  // Erase pixel a few steps back
      strip.show();
      delay(10);
  }
}
