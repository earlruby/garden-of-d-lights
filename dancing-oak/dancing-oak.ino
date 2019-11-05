// Dancing Oak

// Red waves spiral up the sides of an old oak tree, making it appear to spin and dance.

#include <Adafruit_NeoPixel.h>

#define N_LEDS    150     // 10 meter reel @ 30 LEDs/m
#define N_REELS   12      // Use pins 0 through N_REELS-1 to control each reel of NeoPixels 
#define N_SPIRALS 5       // Number of spiraling spirals

Adafruit_NeoPixel reel[N_REELS];

int spiral_width  = 7;     // Width in pixels across reels
int spiral_height = 3;     // Length in pixels along a single reel
int spiral_slope = 1;      // Advance 1 pixel per reel
int spiral_separation = floor(N_LEDS/(N_SPIRALS+1));
int offset = 0;

int spiral[N_SPIRALS][2];    // Per spiral, the current lower left corner's starting reel and pixel
uint32_t color[N_SPIRALS];   // The color of each spiral

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise

  for (int p = 0; p < N_REELS; p++) {
    reel[p] = Adafruit_NeoPixel(N_LEDS, p, NEO_GRB + NEO_KHZ800);
    reel[p].begin();
    reel[p].clear();
  }

  for (int b=0; b < N_SPIRALS; b++) {
    spiral[b][0] = random(0, N_REELS);    // Starting reel for spiral
    spiral[b][1] = b * spiral_separation; // Starting pixel for spiral
  }

  color[0] = 0xFF0000; // Red
  color[1] = 0x8B4000; // Dark Red
  color[2] = 0x800000; // Maroon
  color[3] = 0xFF6347; // Tomato
  color[4] = 0xDC143C; // Crimson Red
  //color[5] = 0xCD5C5C; // Indian Red  
}

void loop() {
  for(int b=0; b < N_SPIRALS; b++) {
    // Draw a frame for each spiral
    draw_spiral(spiral[b][0], spiral[b][1], color[b]);

    // Advance to the next reel
    spiral[b][0]++;
    if (spiral[b][0] >= N_REELS) {
      spiral[b][0] = 0;
    }
    spiral[b][1] += spiral_slope;
    if (spiral[b][1] >= N_LEDS) {
      spiral[b][1] = spiral[b][1] - N_LEDS;
    }
  }
  for (int p = 0; p < N_REELS; p++) {
    reel[p].show();
  }
  delay(35);
}

// Given the lower left-hand corner, draw a single spiral
static void draw_spiral(int starting_reel, int starting_pixel, uint32_t color) {
  // Erase where the spiral was
  int r = starting_reel;
  for(int i=0; i<spiral_height; i++) {
    int pixel = i + starting_pixel;
    // Wrap around to the bottom
    if (pixel >= N_LEDS) {
      pixel = pixel - N_LEDS;
    }
    reel[r].setPixelColor(pixel, 0);
  }

  // Draw where the spiral is
  for (int w=0; w<spiral_width; w++) {
    // Since the starting reel is always the blank row, color starts on the next reel (+1)
    r = starting_reel + 1 + w;
    // Wrap around the reels right to left
    if (r >= N_REELS) {
      r = r - N_REELS;
    }

    for (int h = 0; h < spiral_height; h++) {
      int pixel = h + starting_pixel + ((w + 1) * spiral_slope);
      // Wrap from the top back to the bottom
      if (pixel >= N_LEDS) {
        pixel = pixel - N_LEDS;
      }
      reel[r].setPixelColor(pixel, color);
    }
  }
}
