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

![GoDL 2023](images/2023-12-01%2017.24.02.jpg)

![GoDL 2023](images/2023-12-01%2018.03.59.jpg)

![GoDL 2023](images/2023-12-01%2019.57.56.jpg)

## NeoPixels

I started researching NeoPixels by reading and re-reading the [Adafruit NeoPixel Überguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels).
If you're planning on building anything I recommend that you do the same. The guide is your best place to get started.

I built 3 different NeoPixel installations:

* Dancing Oak - The garden has a 200+ year old Valley Oak tree with a trunk that has a 4m (13 foot) circumference. My plan was to run (12) separate 5m strips
  of NeoPixels up the trunk spaced 0.3m (1 foot) apart and held in place with black bungee cords. The NeoPixels would travel up the trunk into the branches until
  we got to the end of a strip. The lights would pulse up from the earth and make the tree appear to spin and "dance". For the 2023 show I moved the lights from
  the Oak tree to a hillside at the back of the garden where people say it reminds them of a lava flow or large glowing worms.
* Light Stream - There was a dry stream bed in the garden and I wanted to make it light up as if there was water and fish in it. I took (4) 10m NeoPixel strips
  to make the stream. The lights were programmed to pulse in different shades of blue to represent waves of water, while salmon-colored lights swam "upstream".
* Sky Circle - Originally envisisoned as a 40m cicumference circle of lights suspended 4.5m-6m (15-20 feet) in the air, making a rigid circle wasn't practical
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

## Dancing Oak AKA "Lava"

![Dancing Oak control box](images/dancing-oak-2019-11-06-20.50.52.jpg?raw=true "Dancing Oak control box")
![Dancing Oak and Sky Circle control boxes](images/dancing-oak-and-sky-circle-2019-11-07-10.43.38.jpg?raw=true "Dancing Oak and Sky Circle control boxes")

# Light Stream

![Light Stream control box](images/lightstream-construction-2019-10-19-11.50.43.jpg?raw=true "Light Stream control box")


# Sky Circle AKA "Fireflies"

![Sky Circle control box](images/sky-circle-2019-11-08-19.39.08.jpg?raw=true "Sky Circle control box")
