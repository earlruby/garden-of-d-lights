// Sky Circle

// Neopixels arranged in a large circle, suspended 15' in the air.
// Small orbs chase each other around the circle, speed up, slow
// down, change direction, and bounce off one another.

#include <Adafruit_NeoPixel.h>

#define PIN    0       // Arduino signaling pin
#define N_LEDS 600     // 4 x 5 meter reel @ 30 LEDs/m
#define N_ORBS 4       // Number of orbs
#define MAX_SPEED 5    // Maximum speed

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t orbColor[N_ORBS];
uint16_t orbPosition[N_ORBS];   // LED # to light
int orbSpeed[N_ORBS];           // 0 to MAX_SPEED
int orbDirection[N_ORBS];       // 1=forward, -1=backward
bool orbCollide[N_ORBS];     // Has the orb collided since it was last moved?

int speedCtr;
int tPosition;

void setup() {
  randomSeed(analogRead(0));  // Initialize random number generator using analog noise
  speedCtr = 0;
  
  orbColor[0] = 0x008080; // Teal
  orbColor[1] = 0xFF00FF; // Magenta
  orbColor[2] = 0xFFA500; // Orange
  orbColor[3] = 0xFFFFFF; // White

  for (int i = 0; i < N_ORBS; i++) {
    orbPosition[i] = (N_LEDS * i) / N_ORBS;
    orbSpeed[i] = min(i + 2, MAX_SPEED);
    orbDirection[i] = 1;
    orbCollide[i] = false;
  }

  strip.begin();
}

void loop() {
  
  for (int i = 0; i < N_ORBS; i++) {
    // Erase where orb was
    strip.setPixelColor(orbPosition[i], 0);

    // Move the orb
    tPosition = (int) orbPosition[i];
    if (orbSpeed[i] % speedCtr < orbSpeed[i]) {
      tPosition += orbDirection[i];
      orbCollide[i] = false;
    }

    // Wrap around the ends
    if (tPosition >= N_LEDS) {
      tPosition -= N_LEDS;
    }
    if (tPosition < 0) {
      tPosition += N_LEDS;
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
    strip.setPixelColor(orbPosition[i], orbColor[i]);
  }
 
  strip.show();
  //delay(5);
  
  speedCtr++;
  if (speedCtr > MAX_SPEED) {
    speedCtr = 0;
  }
}
