// Sky Circle

// Neopixels arranged in a large circle, suspended 15' in the air.
// Small orbs chase each other around the circle, speed up, slow
// down, change direction, and bounce off one another.

#include <Adafruit_NeoPixel.h>

#define N_LEDS    600     // Per reel: 4 x 5 meter reel @ 30 LEDs/m
#define N_REELS   2       // Use pins 0 through N_REELS-1 to control each reel of NeoPixels
#define N_TOTAL_LEDS 1200 // N_LEDS * N_REELS
#define N_ORBS    6       // Number of orbs
#define MAX_SPEED 4       // Maximum speed

// The Arduino compiler won't let me do this in a loop
int pin = 0;
Adafruit_NeoPixel reel[] = {
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800),
   Adafruit_NeoPixel(N_LEDS, pin++, NEO_GRB + NEO_KHZ800)
};

uint32_t orbColor[N_ORBS];
uint16_t orbPosition[N_ORBS];   // LED # to light
int orbSpeed[N_ORBS];           // 0 to MAX_SPEED
int orbDirection[N_ORBS];       // 1=forward, -1=backward
bool orbCollide[N_ORBS];        // Has the orb collided since it was last moved?

int speedCtr;
int tPosition;

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise
  speedCtr = 0;
  
  orbColor[0] = 0x008080; // Teal
  orbColor[1] = 0xFF00FF; // Magenta
  orbColor[2] = 0xFFA500; // Orange
  orbColor[3] = 0xFFFFFF; // White
  orbColor[4] = 0xFF0800; // Candy Apple
  orbColor[5] = 0x00FF00; // Green

  for (int i = 0; i < N_ORBS; i++) {
    orbPosition[i] = (N_LEDS * i) / N_ORBS;
    orbSpeed[i] = (i % MAX_SPEED) + 2;
    orbDirection[i] = 1;
    orbCollide[i] = false;
  }

  for (int r = 0; r < N_REELS; r++) {
    reel[r].begin();
    reel[r].show();
  }
}

// pixel is a number >= 0 and < N_TOTAL_LEDS
static void draw_pixel(uint16_t pixel, uint32_t color) {
  if (pixel < N_LEDS) {
    // First half is reel 0, pixels are lit from 0 to 599
    reel[0].setPixelColor(pixel, color);
  } else {
    // Second half of the circle is reel 1, pixels are lit from 600 to 0, e.g.:
    // If pixel = 600, light pixel 599
    // If pixel = 601, light pixel 598
    // If pixel = 602, light pixel 597
    // If pixel = 1198, light pixel 1
    // If pixel = 1199, light pixel 0
    reel[1].setPixelColor(N_LEDS - (pixel - N_LEDS) - 1, color);
  }
}

void loop() {

  for (int i = 0; i < N_ORBS; i++) {
    // Erase where orb was
    draw_pixel(orbPosition[i], 0);

    // Move the orb
    tPosition = (int) orbPosition[i];
    if (orbSpeed[i] % speedCtr < orbSpeed[i]) {
      tPosition += orbDirection[i];
      orbCollide[i] = false;
    }

    // Wrap around the ends
    if (tPosition >= N_TOTAL_LEDS) {
      tPosition -= N_TOTAL_LEDS;
    }
    if (tPosition < 0) {
      tPosition += N_TOTAL_LEDS;
    }
    orbPosition[i] = (uint16_t) tPosition;

    // Check for collisions
    for (int a = 0; a < N_ORBS; a++) {
      for (int b = a+1; b < N_ORBS; b++) {
        if (orbPosition[a] == orbPosition[b] and orbCollide[a] == false and orbCollide[b] == false) {
          
          // Transfer momentum
          int speed = orbSpeed[a];
          orbSpeed[a] = orbSpeed[b];
          orbSpeed[b] = speed;

          if (orbDirection[a] == orbDirection[b]) {
            // If both orbs are heading in the same direction, change the direction of 1
            orbDirection[b] *= -1;
          } else {
             // Change direction
             orbDirection[a] *= -1;
             orbDirection[b] *= -1;           
          }

          // Don't recalculate collisions until the orb has been moved
          orbCollide[a] = true;
          orbCollide[b] = true;
        }
      }
    }
 
    // Draw where the orb is now
    draw_pixel(orbPosition[i], orbColor[i]);
  }

  reel[0].show();
  reel[1].show();
  
  speedCtr++;
  if (speedCtr > MAX_SPEED) {
    speedCtr = 0;
  }
}
