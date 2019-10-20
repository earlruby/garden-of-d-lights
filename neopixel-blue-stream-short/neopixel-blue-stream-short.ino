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
uint32_t fish_color[N_FISH];

uint8_t brightness[N_REELS];

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise

  int initial_fish_spacing = 30;
  for (int p = 0; p < N_REELS; p++) {
    strip[p] = Adafruit_NeoPixel(N_LEDS, p, NEO_GRB + NEO_KHZ800);
    strip[p].begin();
    
    for (int f = 0; f < N_FISH; f++) {
      fish[f][p]= strip[p].numPixels() - 1 - (f * initial_fish_spacing);
    }

    // Initialize all strips to fully bright
    brightness[p] = 255;

    // Clear the reels
    strip[p].clear();
  }

  fish_color[0] = 0xFF6666;
  fish_color[1] = 0xFFCC66;
  fish_color[2] = 0xFFFF99;
  
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
  uint16_t bands = 6;
  uint16_t band_length = floor(strip[0].numPixels()/bands);
  
  for(uint16_t i=0; i<band_length; i++) {
    
    for (int p = 0; p < N_REELS; p++) {
      for (int f = 0; f < N_FISH; f++) {
        strip[p].setPixelColor(fish[f][p], c);   // Erase previous fish with water color
  
        // Move the fish upstream 2/5 of the time
        if (random(1, 6) < 3) {
          fish[f][p]--;
        }
        // Move the fish back to the bottom of the stream
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

    // Fish swimming upstream
    for (int p = 0; p < N_REELS; p++) {
      for (int f = 0; f < N_FISH; f++) {
        strip[p].setPixelColor(fish[f][p], fish_color[f]);
      }
    }
/*
    // Vary the brightness of the strips
    for (int p = 0; p < N_REELS; p++) {
      brightness[p] += random(-10, 10);
      if (brightness[p] > 255) {
        brightness[p] = 255;
      }
      if (brightness[p] < 100) {
        brightness[p] = 100;
      }
    }
*/
    for (int p = 0; p < N_REELS; p++) {
      strip[p].setBrightness(brightness[p]);
      strip[p].show();
    }
    delay(60);
  }
}
