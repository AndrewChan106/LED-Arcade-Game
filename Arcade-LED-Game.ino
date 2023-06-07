#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int randomStationaryLED;
int CirclingLED = 0;
int circleDelayTime = 125;
int timesCorrect = 0;
bool resetButton = 0;

const int rightButton = 5;
volatile int rightButtonFlag = 0;
const int leftButton = 4;
volatile int leftButtonFlag = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  // delay_halfs.start(500,AsyncDelay::MILLIS);
  CircuitPlayground.setBrightness(7);
  attachInterrupt(digitalPinToInterrupt(4), stopGreenLight, RISING);
  attachInterrupt(digitalPinToInterrupt(5), resetting, RISING);
  randomStationaryLED = random(0, 10);
}

void loop() {
  CircuitPlayground.setPixelColor(CirclingLED, 0, 255, 0);
  CircuitPlayground.setPixelColor(randomStationaryLED, 255, 0, 0);
  if(CirclingLED == randomStationaryLED)
  {
    CircuitPlayground.setPixelColor(CirclingLED, 0, 0, 255);
    CircuitPlayground.setPixelColor(randomStationaryLED, 0, 0, 255);
    if (leftButtonFlag == 1)
    {
      delay(10);
      if (timesCorrect < 2)
      {
      circleDelayTime -=25;
      timesCorrect++;
      }
      else
      {
        delay(10);
        for(int p = 0; p < 10; p++)
        {
          CircuitPlayground.setPixelColor(p, 0, 255, 0);
        }
        while (resetButton == 0)
        {
        delay(10);
        }
      }
    leftButtonFlag = 0;
    }
  }
  leftButtonFlag = 0;
  resetButton = 0;
  CirclingLED++; 
    if(CirclingLED > 9)
  {
    CirclingLED = 0;
  }
    delay(circleDelayTime);
    Serial.println(circleDelayTime);
  CircuitPlayground.clearPixels();
  // randomStationaryLED = random(0, 10);
  // CircuitPlayground.setPixelColor(randomStationaryLED, 255, 0, 0);
}

void stopGreenLight(){
  leftButtonFlag = 1;
}

void resetting(){
  rightButtonFlag = 1;
  resetButton = 1;
  timesCorrect = 0;
  circleDelayTime = 125;
}

