
#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int presets[6][2][3] = {
  {
    {27, 167, 132},    //color of first LED in preset 0 (green)
    {152, 54, 128}    //color of second LED (purple)

  },
  {
    {0, 0, 255}, //color of first LED in preset 1 (blue)
    {254, 215, 26}    //yellow

  },
  {
    {237, 51, 51}, //color of first LED in preset 1 (red)
    {236, 155, 173}   //pink
  },
  {
    {250, 126, 35}, //color of first LED in preset 1 (red)
    {185, 222, 201}   //pink
  },
  {
    {248, 223, 112}, //color of first LED in preset 1 (yellow)
    {100, 88, 34}   //dark green
  }
  ,
  {
    {204, 22, 58}, //color of first LED in preset 1 (red)
    {34, 62, 54}   //dark green
  }
};

int preset = 0;

float tempC;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //  colorWipe(strip.Color(255, 0, 0), 50); // Red
  // colorWipe(strip.Color(0, 255, 0), 50); // Green
  // colorWipe(strip.Color(0, 0, 255), 50); // Blue
  //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue

  //rainbow(20);
  // rainbowCycle(20);
  //theaterChaseRainbow(50);

  //only shake to start color
  float acc = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
  if (acc > 25) {
    //rainbow(20);
    preset = rand() % 5;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor (i, presets[preset][i % 2][0], presets[preset][i % 2][1], presets[preset][i % 2][2]);
  }
  strip.show();

  //temperature sensor: if the temperature is over 30, it will turn into rainbow,or else normal
  tempC = CircuitPlayground.temperature();

  if (tempC > 30) {
    rainbow(20);
  } else {
    float acc = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());
    if (acc > 25) {
      //rainbow(20);
      preset = rand() % 5;
    }

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor (i, presets[preset][i % 2][0], presets[preset][i % 2][1], presets[preset][i % 2][2]);
    }
    strip.show();
  }


}



void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255)); //set color on neopixel strip
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
