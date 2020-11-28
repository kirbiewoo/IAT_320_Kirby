#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


//slouch units
#define SLOUCH_ANGLE  10.0
#define SLOUCH_TIME   30  //this is 3 sec
#define GRAVITY       9.80665
#define RAD2DEG       57.29579

float value;

//slouch
float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
uint8_t pixeln = 0;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6
#define LED_COUNT  30

#define BRIGHTNESS 50

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  Serial.begin(9600);
  CircuitPlayground.begin();
  targetAngle = 0;

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
  //sound
  value = CircuitPlayground.mic.soundPressureLevel(100);

  Serial.print("Sound Sensor SPL: ");
  Serial.println(value);

  if (value > 80) {
    //strip.setPixelColor(colorWipe);         //  Set pixel's color (in RAM)                       //  Pause for a moment
    theaterChase(strip.Color(127, 127, 127), 200); // White
    //delay(100);
    if (pixeln == 10) {
      pixeln = 0;
      CircuitPlayground.clearPixels();
    }
  } else if (value > 60) {
    theaterChase(strip.Color(22, 97, 195), 200); // Blue
   
    //  Pause for a moment
    //delay(300);
    strip.show();
    if (pixeln == 10) {
      pixeln = 0;
      CircuitPlayground.clearPixels();
    }
    else {
       theaterChase(strip.Color(240, 55, 82), 200); // pink
    }
  }
  // delay(100);

  //slouch
  //currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);

 // if ( ( CircuitPlayground.leftButton()) || ( CircuitPlayground.rightButton())) {
    // if either is pressed
  //  targetAngle = currentAngle;
  //}

 // if (currentAngle - targetAngle > SLOUCH_ANGLE) {
  //  if (!slouching) {
  //    strip.show();
   //   slouchStartTime = millis();
  //    slouching = true;
  //  }
 // }
  //else {
  //  slouching = false;
  //}

  //if (slouching) {
  //  strip.show();
  //  rainbow(20);
  //}
  //delay(10);
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
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
