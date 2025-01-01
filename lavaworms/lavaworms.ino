// Lava Worms

// Waves of blue and green pulsing up 12 x 5m strands of NeoPixel
// lights running across the ground from agave to agave.

// This is the same code and hardware used for the Dancing Oak,
// now installed on the ground rather than running up the sides
// of an Oak Tree.

// NeoPixel data wires plugged into Arduino pins 0-11, NeoPixel
// ground wires all connected to common ground. NeoPixel power
// lines plugged into two 5V 20A brick power supplies.

#include <Adafruit_NeoPixel.h>

#define N_LEDS  150     // 5 meter reel @ 30 LEDs/m
#define N_REELS 12      // Use pins 0 through N_REELS-1 to control each reel of NeoPixels

// The Arduino compiler won't let me do this in a loop
int pin = 0;
Adafruit_NeoPixel strip[] = {
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800)
};

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise
  for (int p = 0; p < N_REELS; p++) {
    strip[p].begin();
  }
}

uint32_t r_inc = 0x110000;
uint32_t g_inc = 0x001100;
uint32_t b_inc = 0x000011;

void loop() {
  stream(0x960018, r_inc); // Red Pink
  stream(0xFF0000, r_inc); // Red
  stream(0xFF00FF, r_inc); // Magenta
  stream(0xFF0800, r_inc); // Candy Apple
  stream(0xDC143C, r_inc); // Crimson Red
  stream(0xFF4500, r_inc); // Orange Red
  stream(0xE0115F, r_inc); // Pink
  stream(0x7F00FF, r_inc); // Violet
  stream(0x336EFF, b_inc); // Darker blue
  stream(0x33F6FF, b_inc); // Lighter blue
  stream(0x20B2AA, g_inc); // Light sea green
  stream(0x00FF7F, g_inc); // Spring Green
  stream(0x32CD32, g_inc); // Lime Green
  stream(0x00FF00, g_inc); // Lime
  stream(0xFFFF00, b_inc); // Green Yellow
  stream(0x7FFF00, b_inc); // Chartreuse
  stream(0x8B4000, b_inc); // Warm Yellow

}

static void stream(uint32_t c, uint32_t c_inc) {
  uint16_t pixels_to_light = 11;
  uint16_t bands = 5;
  uint16_t band_length = floor(strip[0].numPixels()/bands);
  uint16_t same_color_repeat = random(12, 15);

  for(uint16_t j=0; j<same_color_repeat; j++) {
    for(uint16_t i=0; i<band_length; i++) {
      for(uint16_t b=0; b<bands; b++) {
        for (int p = 0; p < N_REELS; p++) {
          strip[p].setPixelColor(i+(b*band_length), c);                  // Draw new pixel
          strip[p].setPixelColor(i+(b*band_length)-pixels_to_light, 0);  // Erase pixel a few steps back
        }
      }

      // Erase the last pixels on the strip from the previous run
      if (i<=pixels_to_light) {
        for (int p = 0; p < N_REELS; p++) {
          strip[p].setPixelColor(strip[p].numPixels()-1-pixels_to_light+i, 0);
        }
      }

      for (int p = 0; p < N_REELS; p++) {
        strip[p].show();
      }
      delay(5);
    }
    c += c_inc;
  }
}
