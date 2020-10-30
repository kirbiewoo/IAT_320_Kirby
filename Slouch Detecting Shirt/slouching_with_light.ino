#include <Adafruit_CircuitPlayground.h>

//macro
#define SLOUCH_ANGLE  10.0          //how much you can slouch
#define SLOUCH_TIME   3000         //3 SECONDS
#define SLOUCH_TEN   8000         //10 SECONDS
#define GRAVITY       9.80665     //gravity
#define RADZDEG       57.29579   //180/3.1415 (pie)
#define FLASH_RATE    50
#define SPIN_RATE     100
#define COLOR         0xff07ee
#define COLOR1        0xFF5500
#define badPostureCount

float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching = false;

int pixel1;
int pixel2;


void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  Serial.begin(9600);
  targetAngle = 0;   // what the user set by pressing one of the button, initialize
  CircuitPlayground.setBrightness(255); //Set brightness of neopixels

  pixel1 = 0;
  pixel2 = 5;
}

void loop() {
  // put your main code here, to run repeatedly:

  currentAngle = RADZDEG * asin(-CircuitPlayground.motionZ() / GRAVITY);

  Serial.println(currentAngle);

  //press the button to initialize angle

  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900, 100);
    delay(100);
    CircuitPlayground.playTone(900, 100);
    delay(100);
  }

  //detects slouch
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) {
      slouchStartTime = millis();  //current millisecond
      slouching = true;
    }
  } else {
    slouching = false;
    CircuitPlayground.clearPixels();
  }
  if (slouching) {
    if (millis() - slouchStartTime > SLOUCH_TIME) {     //3 SECONDS
      CircuitPlayground.playTone(100, 500);
      delay (500);
    }
    if (slouching) {
      if (millis() - slouchStartTime > SLOUCH_TEN) {     //3 SECONDS
        CircuitPlayground.playTone(1760, 500);
        for (int pixel = 0; pixel < 10; pixel ++) {
          CircuitPlayground.setPixelColor(pixel1, COLOR);
          CircuitPlayground.setPixelColor(pixel2, COLOR1);

          pixel1 = pixel1 + 1;
          pixel2 = pixel2 + 1;

          if (pixel1 > 9) pixel1 = 0;
          if (pixel2 > 9) pixel2 = 0;

          delay(SPIN_RATE);
        }
        delay(FLASH_RATE);
        CircuitPlayground.clearPixels();
        delay(FLASH_RATE);
      }
    }
  }
}
