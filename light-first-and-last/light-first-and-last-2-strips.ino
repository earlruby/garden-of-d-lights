// Light first and last

// Light the first and last lights in a strip, to verify signalling.
// LEDs are numbered 0 to (N_LEDS-1)

#include <Adafruit_NeoPixel.h>

#define PIN0    0       // Arduino signaling pin
#define PIN1    1       // Arduino signaling pin
#define N_LEDS 150      // 4 x 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip[2] = {
  Adafruit_NeoPixel(N_LEDS, PIN0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(N_LEDS, PIN1, NEO_GRB + NEO_KHZ800)
};

void setup() {
  strip[0].begin();
  strip[0].show();
  strip[1].begin();
  strip[1].show();
}

void loop() {
  strip[0].setPixelColor(0, 0xFFFFFF); // White
  strip[0].setPixelColor(N_LEDS-1, 0xFFFFFF); // White
  strip[0].setPixelColor(1, 0x0000FF); // Blue
  strip[0].setPixelColor(N_LEDS-2, 0x0000FF); // Blue
  strip[0].setPixelColor(2, 0xFF0000); // Red
  strip[0].setPixelColor(N_LEDS-3, 0xFF0000); // Red
  strip[1].setPixelColor(0, 0); // Clear
  strip[1].setPixelColor(N_LEDS-1, 0); // White
  strip[1].setPixelColor(1, 0x0000FF); // Blue
  strip[1].setPixelColor(N_LEDS-2, 0x0000FF); // Blue
  strip[1].setPixelColor(2, 0); // Red
  strip[1].setPixelColor(N_LEDS-3, 0); // Red
  strip[0].show();
  strip[1].show();
}
