// Multi-reel test

// Waves of blue pulsing down multiple 5m strands of NeoPixel lights.
// NeoPixel data wires plugged into Arduino pins 0-n, NeoPixel
// ground wires all connected to common ground. NeoPixel power
// lines plugged into 5V 20A brick power supply. 

#include <Adafruit_NeoPixel.h>

#define N_LEDS  150     // 10 meter reel @ 30 LEDs/m
#define N_REELS 12      // Use pins 0 through N_REELS-1 to control each reel of NeoPixels 

Adafruit_NeoPixel strip[N_REELS];

void setup() {
  for (int p = 0; p < N_REELS; p++) {
    strip[p] = Adafruit_NeoPixel(N_LEDS, p, NEO_GRB + NEO_KHZ800);
    strip[p].begin();

    // Clear the reels
    strip[p].clear();
  }  
}

void loop() {
  stream(0x33F6FF); // Lighter blue
  stream(0x33B5FF);
  stream(0x33DDFF);
  stream(0x33D1FF);
  stream(0x33CAFF);
  stream(0x33C1FF);
  stream(0x3341FF);
  stream(0x334EFF);
  stream(0x3351FF);
  stream(0x336EFF); // Darker blue
}

static void stream(uint32_t c) {
  uint16_t pixels_to_light = 5;
  uint16_t bands = 5;
  uint16_t band_length = floor(strip[0].numPixels()/bands);
  
  for(uint16_t i=0; i<band_length; i++) {
    
    // Draw colored blue bands for waves
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
    delay(60);
  }
}
