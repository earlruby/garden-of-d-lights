// Dancing Oak

// Red waves spiral up the sides of an old oak tree, making it appear to spin and dance.

#include <Adafruit_NeoPixel.h>

#define N_LEDS    150     // 10 meter reel @ 30 LEDs/m
#define N_REELS   12      // Use pins 0 through N_REELS-1 to control each reel of NeoPixels 
#define N_SPIRALS 8       // Number of spirals
#define N_COLORS  6       // Number of different colors

// The Arduino compiler won't let me do this in a loop
int pin = 0;
Adafruit_NeoPixel reel[] = {
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

uint16_t spiral_width  = 10;    // Width in pixels across reels
uint16_t spiral_height = 6;     // Length in pixels along a single reel
uint16_t spiral_slope = 1;      // Advance 1 pixel per reel
uint16_t spiral_separation = floor(N_LEDS/(N_SPIRALS));

int spiral_starting_reel[N_SPIRALS];       // Per spiral, the current lower left corner's starting reel
uint16_t spiral_starting_pixel[N_SPIRALS]; // Per spiral, the current lower left corner's starting reel
int spiral_color[N_SPIRALS];               // The index of the color of each spiral
uint32_t color[N_COLORS];                  // The available colors

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise

  for (int p = 0; p < N_REELS; p++) {
    reel[p].begin();
    reel[p].show();
  }

  for (int b=0; b < N_SPIRALS; b++) {
    spiral_starting_reel[b]  = random(0, N_REELS);                   // Starting reel for spiral
    spiral_starting_pixel[b] = ((uint16_t) b) * spiral_separation;   // Starting pixel for spiral
    spiral_color[b] = random(0, N_COLORS);                           // Starting index of the color of each spiral
  }

  color[0] = 0x960018; // Red
  color[1] = 0xFF0800; // Candy Apple
  color[2] = 0xFF00FF; // Magenta
  color[3] = 0xDC143C; // Crimson Red
  color[4] = 0x7F00FF; // Violet
  color[5] = 0xE0115F; // Pink
  //color[6] = 0xFFFF00; // Green Yellow
  //color[7] = 0x8B4000; // Warm Yellow
}

void loop() {

  // Draw the spirals
  for(int b=0; b < N_SPIRALS; b++) {
    // Draw a frame for each spiral
    draw_spiral(spiral_starting_reel[b], (uint16_t) spiral_starting_pixel[b], color[spiral_color[b]]);

    // Advance to the next reel
    spiral_starting_reel[b]++;
    if (spiral_starting_reel[b] >= N_REELS) {
      spiral_starting_reel[b] = 0;
    }
    // Wrap from top to bottom
    spiral_starting_pixel[b] += spiral_slope;
    if (spiral_starting_pixel[b] >= N_LEDS) {
      spiral_starting_pixel[b] = spiral_starting_pixel[b] - N_LEDS;
    }

    // Randomly change a color
    if (random(0,500) == 0) {
      spiral_color[b] = random(0, N_COLORS);
    }
  }
  
  for (int p = 0; p < N_REELS; p++) {
    reel[p].show();
  }
  delay(150);
}

// Given the lower left-hand corner, draw a single spiral
static void draw_spiral(int starting_reel, uint16_t starting_pixel, uint32_t color) {
  // Erase where the spiral was
  int r = starting_reel;
  for(uint16_t i=0; i<spiral_height; i++) {
    uint16_t pixel = i + starting_pixel;
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

    for (uint16_t h = 0; h < spiral_height; h++) {
      uint16_t pixel = h + starting_pixel + (((uint16_t)(w + 1)) * spiral_slope);
      // Wrap from the top back to the bottom
      if (pixel >= N_LEDS) {
        pixel = pixel - N_LEDS;
      }
      reel[r].setPixelColor(pixel, color);
    }
  }
}
