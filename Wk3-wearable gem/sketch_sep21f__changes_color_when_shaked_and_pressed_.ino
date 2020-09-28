#include <Adafruit_CircuitPlayground.h>

int presets[3][2][3] = {
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

  }
};

int preset = 0;
bool lastRightPress = false;
bool lastLeftPress = false;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  // float total = abs(CircuitPlayground.motionX()) +
  //              abs(CircuitPlayground.motionY()) + abs(CircuitPlayground.motionZ());

  // if (CircuitPlayground.rightButton()) {
  // do something

  //}

  bool leftPress = CircuitPlayground.leftButton();
  if (leftPress && (lastLeftPress == false)) {
    preset = ((preset - 1) + 3) % 3;
  }
  lastLeftPress = leftPress;

  bool rightPress = CircuitPlayground.rightButton();
  if (rightPress && (lastRightPress == false)) {
    preset = (preset + 1) % 3;
  }
  lastRightPress = rightPress;

  float acc = abs(CircuitPlayground.motionX()) + abs (CircuitPlayground.motionY()) + abs (CircuitPlayground.motionZ());
  if (acc > 25) {
    preset = rand() % 3;
  }


  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor (i, presets[preset][i % 2][0], presets[preset][i % 2][1], presets[preset][i % 2][2]);
  }


  //Serial.println(total);
  delay (10);
}
