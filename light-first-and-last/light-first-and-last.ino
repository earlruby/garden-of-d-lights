// Light first and last

// Light the first and last lights in a strip, to verify signalling.
// LEDs are numbered 0 to (N_LEDS-1)

#include <Adafruit_NeoPixel.h>

#define PIN    0       // Arduino signaling pin
#define N_LEDS 600     // 4 x 5 meter reel @ 30 LEDs/m

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop() {
  strip.setPixelColor(0, 0xFFFFFF); // White
  strip.setPixelColor(N_LEDS-1, 0xFFFFFF); // White
  strip.setPixelColor(1, 0x0000FF); // Blue
  strip.setPixelColor(N_LEDS-2, 0x0000FF); // Blue
  strip.setPixelColor(2, 0xFF0000); // Red
  strip.setPixelColor(N_LEDS-3, 0xFF0000); // Red
  strip.show();
}
