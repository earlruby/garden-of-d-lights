# garden-of-d-lights
Arduino code used to run the Garden of d'Lights at the Ruth Bancroft Garden.

## The Ruth Bancroft Garden

In December 2018 I was asked if I would like to put together a light show to light uup the plants at
[The Ruth Bancroft Garden](https://www.ruthbancroftgarden.org/) in Walnut Creek, California. A garden named
*The most beautiful garden in the world* by [Tripadvisor](https://www.travelandleisure.com/ruth-bancroft-garden-walnut-creek-california-named-most-beautiful-in-world-tripadvisor-data-study-8700410).

I spent the next year researching LED and laser lighting to create some unique lighting installations for the garden.
Some of the installations used NeoPixel LED strips and many people have asked me how I created these lights, so
I am documenting these installations here.

![Earl Ruby at The Garden of D'Lights 2023](images/20240103_193827.jpg "Earl Ruby at The Garden of D'Lights")

![GoDL 2023 - Valley Oak with color-changing Japanese Lanterns](images/2023-12-01%2017.24.02.jpg "GoDL 2023 - Valley Oak with color-changing Japanese Lanterns")

![GoDL 2023 - LED lighting on plants behind the pond](images/2023-12-01%2018.03.59.jpg "GoDL 2023 - LED lighting on plants behind the pond")

![GoDL 2023 - LED lighting on agaves](images/2023-12-01%2019.57.56.jpg "GoDL 2023 - LED lighting on agaves")

![GoDL 2020 - Koi Pond](images/2020-12-11%2019.53.01.jpg "GoDL 2020 - Koi Pond")

## NeoPixels

I started researching NeoPixels by reading and re-reading the [Adafruit NeoPixel Überguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels).
If you're planning on building anything I recommend that you do the same. The guide is your best place to get started.

I built 3 different NeoPixel installations:

* **Dancing Oak** - The garden has a 200+ year old Valley Oak tree with a trunk that has a 4m (13 foot) circumference. My plan was to run (12) separate 5m strips
  of NeoPixels up the trunk spaced 0.3m (1 foot) apart and held in place with black bungee cords. The NeoPixels would travel up the trunk into the branches until
  we got to the end of a strip. The lights would pulse up from the earth and make the tree appear to spin and "dance". For the 2023 show I moved the lights from
  the Oak tree to a hillside at the back of the garden where people say it reminds them of a lava flow or large glowing worms.
* **Light Stream** - There was a dry stream bed in the garden and I wanted to make it light up as if there was water and fish in it. I took (4) 10m NeoPixel strips
  to make the stream. The lights were programmed to pulse in different shades of blue to represent waves of water, while salmon-colored lights swam "upstream".
* **Sky Circle** - Originally envisisoned as a 40m cicumference circle of lights suspended 4.5m-6m (15-20 feet) in the air, making a rigid circle wasn't practical
  for the site so I ended up using steel cable mounted to three trees in the garden's Eyucalyptus Grove and created a "Sky Triangle" instead. The effect still
  works, and mesmerizes people passing through the grove every night of the event. Many guests refer to the effect as "fireflies" or "glowing orbs", six lights
  chase each other around the sides of the triangle, sometimes passing through one another and sometimes bouncing off each other.

For all three installations I used:

* An Arduino "Mega" microcontroller.
* One or two 5VDC @ 20A "brick" power supplies.
* A 1000uF capacitor connected across the DC power supply to protect the Arduino and NeoPixels from power surges.
* A 470 Ohm resistor between the Arduino data pins and the NeoPixel signal line for each NeoPixel strip connected to the Arduino.
* A waterproof case.
* Cable glans waterproof cable connectors on each case.
* 3-wire twist-to-connect waterproof cable connectors, one end soldered to the NeoPixel strip, one end going through the case to connect to the Arduino and power
  supply connectors inside the case.
* Terminal screw blocks for connecting cables to power.

An Arduino is a simple microcontroller that can be programmed to do simple tasks, such as to send a signal to a NeoPixel strip that tells Pixel #117 to glow purple.
An Arduino will send whatever signals you tell it to send, over and over and over again, for as long as it has power. To program an Arduino you use a USB cable
connected between your laptop and the Arduino. You write the code on your laptop, send it

Each NeoPixel strip is controlled by 3 wires: black (GND), red (+5VDC), and yellow (signaling, sometimes labeled DIN). The 5VDC @ 20A "brick" power supplies I use have a barrel connector
on the end, but if you cut that off you'll find 2 wires inside the cable: black (GND) and red (+5VDC). If your project requires more power you can get a supply that provides more amps
or connect two 5VDC 20A supplies in parallel (red to red, black to black) to provide 5VDC up to 40A.

For what it's worth, a single 5VDC@20A supply running at maximum capacity is drawing ~1A from the 110VAC wall socket, so it's not using a lot of power, put it can still kill you. Be
careful when you're working around live electrical sources.

To get a strip to work you have to connect the NeoPixel's DC+ to the power supply's DC+ (red to red), the NeoPixel's GND to the power supply's GND and the Arduino's GND (black to black),
and the NeoPixel's signalling wire through a 370 Ohm resistor to one of the digital signalling pins on the Arduino. You also need to provide power to the Arduino itself. Refer to the
[Adafruit NeoPixel Überguide Basic Connections page](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections) for details.

## Testing NeoPixels

To test a strip I attach the NeoPixel signalling wire to pin 0 on the Arduino and run the [neopixel-test-single-strand.ino](neopixel-test-single-strand/neopixel-test-single-strand.ino)
code. This code is set up for (1) 150 LED NeoPixel strip (a 5m strip with 30 LEDs/m). If that doesn't match what you have just modify the constants to match what you're using. If it works
you should see blue light pulse through the entire strip, as shown in the video below:

https://github.com/earlruby/garden-of-d-lights/blob/main/images/neopixel-test-2019-05-18-16.48.13.mov

I also wrote some test code to [light the first and last pixels on a strip](light-first-and-last/) (handy when you're soldering multiple strips together) and some code to [test multiple strips at once](neopixel-multi-reel-test/neopixel-multi-reel-test.ino).

## Dancing Oak AKA "Lava Worms"

![Dancing Oak control box](images/dancing-oak-2019-11-06-20.50.52.jpg?raw=true "Dancing Oak control box")
![Dancing Oak and Sky Circle control boxes](images/dancing-oak-and-sky-circle-2019-11-07-10.43.38.jpg?raw=true "Dancing Oak and Sky Circle control boxes")

The [original code used in 2019 for the Dancing Oak](dancing-oak/dancing-oak.ino) used multiple colors rotating around and twisting up the oak tree. However, because of the fact that
the lights were not well-aligned left to right the effect was diminished. I though of programming an offset number of LEDs per light strand so that a strand that was 5 LEDs "lower" than
the one next to it would be offset by 5 LEDs and then the lights would line up left to right, and then reprogramming the controller after installation with the "as installed" offset, but
due to the uneven nature of the oak's trunk an offset that worked at the base might start to look "off" 1 or 2m up the tree, so I abandoned that idea.

Instead [I changed the entire program in 2020](dancing-oak-2020/dancing-oak-2020.ino) and made the lights go from the base of the tree pulsing up, abandoning the counter-clockwise sprial.

In 2023 I installed color-changing Japanese Lanterns in the oak tree and moved the NeoPixel installation to a hillside at the back of the garden, where most guests decided that it reminded
them of [lava or worms](lavaworms/lavaworms.ino).

https://github.com/user-attachments/assets/38664de9-6034-44f9-b996-b6a3b1b91b18

# Light Stream

![Light Stream control box](images/lightstream-construction-2019-10-19-11.50.43.jpg?raw=true "Light Stream control box")

For the [Light Stream](light-stream/light-stream.ino) I took (8) 5m NeoPixel strips and soldered them to make (4) 10m strips. Then I attached them to an Arduino Mega programmed to pulse
in different shades of blue to represent waves of water, while salmon-colored lights swam "upstream". I installed the strips in a winding dry stream bed.

https://github.com/earlruby/garden-of-d-lights/blob/main/images/lightstream-2021-11-12-19.56.13.mov


# Sky Circle AKA "Fireflies"

For the Sky Circle I originally took (8) 5m NeoPixel strips and connected them all together to make one long 40m strip. However, I found out that the signal strength of an Arduino Mega
drops off after about 25m, so I couldn't get a consistent, stable signal to the LEDs at the end of the strip.

Since it was a circle I solved the problem by splitting the strip into (2) 20m sections and connecting both to the the Arduino, so the 2 signalling pins each controlled half the circle.
On the far side of the circle I physically attached the two strips together using heat shrink tubing, but didn't make an electrical connection. Then I just had to write the
[Sky Circle Arduino software](sky-circle/sky-circle.ino) so that one pin controlled the first half of the circle and one pin controlled the other half.

![Sky Circle control box](images/sky-circle-2019-11-08-19.39.08.jpg?raw=true "Sky Circle control box")

https://github.com/earlruby/garden-of-d-lights/blob/main/images/sky-circle-2020-12-20-19.51.42.mov
