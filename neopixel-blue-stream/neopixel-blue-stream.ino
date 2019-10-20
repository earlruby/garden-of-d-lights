// Blue Stream.

// Waves of blue pulsing down 4 x 30m strands of NeoPixel lights.
// NeoPixel data wires plugged into Arduino pins 0-3, NeoPixel
// ground wires all connected to common ground. NeoPixel power
// lines plugged into 5V 20A brick power supply. 

#include <Adafruit_NeoPixel.h>

#define N_LEDS  150     // 10 meter reel @ 30 LEDs/m
#define N_REELS 4       // Use pins 0 through N_REELS-1 to control each reel of NeoPixels 
#define N_FISH  3       // Number of fish swimming upstream per reel

Adafruit_NeoPixel strip[N_REELS];
uint16_t fish[N_FISH][N_REELS];

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise

  int initial_fish_spacing = 50;
  for (int p = 0; p < N_REELS; p++) {
    strip[p] = Adafruit_NeoPixel(N_LEDS, p, NEO_GRB + NEO_KHZ800);
    for (int f = 0; f < N_FISH; f++) {
      fish[f][p]= strip[p].numPixels() - 1 - (f * initial_fish_spacing);
    }
    strip[p].begin();
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
  uint16_t pixels_to_light = 15;
  uint16_t bands = 12;
  uint16_t band_length = floor(strip[0].numPixels()/bands);
  
  for(uint16_t i=0; i<band_length; i++) {
    for (int p = 0; p < N_REELS; p++) {
      for (int f = 0; f < N_FISH; f++) {
        strip[p].setPixelColor(fish[f][p], c);   // Erase previous fish with water color
  
        // Move the fish upstream 2/5 of the time
        if (random(1, 6) < 3) {
          fish[f][p]--;
        }
        if (fish[f][p] == 0) {
          fish[f][p] = strip[p].numPixels()-1;
        }
      }
    }
    
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
      for (int f = 0; f < N_FISH; f++) {
        strip[p].setPixelColor(fish[f][p], 0xFF6666);  // Fish swimming upstream
      }
    
      strip[p].show();
    }
    delay(35);
  }
}
