#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int randomStationaryLED;
int CirclingLED = 0;
int circleDelayTime = 200;
int timesCorrect = 0;
int timesIncorrect = 0;
bool resetButton = 0;
int score = 0;

float midi[127];
int A_four = 440;

const int rightButton = 5;
volatile int rightButtonFlag = 0;
const int leftButton = 4;
volatile int leftButtonFlag = 0;
const int flipSwitch = 7;
int switchState = 0;
volatile int flipSwitchFlag = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  // delay_halfs.start(500,AsyncDelay::MILLIS);
  while(!Serial);
  CircuitPlayground.setBrightness(7);
  attachInterrupt(digitalPinToInterrupt(4), stopGreenLight, RISING);
  attachInterrupt(digitalPinToInterrupt(5), resetting, RISING);
  attachInterrupt(digitalPinToInterrupt(7), differentMode, CHANGE);
  generateMIDI(); // Custom function for calculating and storing the frequency value associated for each MIDI pitch number
  randomSeed(analogRead(0));
  randomStationaryLED = random(0, 10);
  Serial.println("Rules");
  Serial.println("-Stop the spinning green LED when it reaches the red LED by pressing the left LED(D4)");
  Serial.println("-Do this three times and you win!");
  Serial.println("-Fail once and you lose; don't worry press the right LED(D5) to reset");
  Serial.println("-Want an endless mode? Flip the switch and track your score on the serial monitor");
  while(leftButtonFlag == 0 && rightButtonFlag == 0)
  {
    sparkleWhite();
  }
  delay(100);
switchState = digitalRead(7);
    if(switchState)
    Serial.println("Normal Mode");
    else
    Serial.println("Unlimited Mode");
  leftButtonFlag = 0;
  rightButtonFlag = 0;
}

void loop() {
  if(flipSwitchFlag)
  {
    delay(10);
      rightButtonFlag = 1;
   resetButton = 1;
   timesCorrect = 0;
    timesIncorrect = 0;
    circleDelayTime = 200;
    switchState = digitalRead(7);
    score = 0;
    if(switchState)
    Serial.println("Normal Mode");
    else
    Serial.println("Unlimited Mode");
    flipSwitchFlag = 0;
  }

if(!switchState)
{
  CircuitPlayground.setPixelColor(CirclingLED, 0, 255, 0);
  CircuitPlayground.setPixelColor(randomStationaryLED, 255, 0, 0);
  if(CirclingLED == randomStationaryLED)
  {
    CircuitPlayground.setPixelColor(CirclingLED, 0, 0, 255);
    CircuitPlayground.setPixelColor(randomStationaryLED, 0, 0, 255);
  }
    delay(circleDelayTime);
   if (leftButtonFlag == 1)
   {
     delay(10);
     if(CirclingLED == randomStationaryLED)
     {
      circleDelayTime -= 10;
      score++;
      Serial.println(score);
      CircuitPlayground.playTone(midi[60], 200);
      leftButtonFlag = 0;
      }
    if(CirclingLED != randomStationaryLED)
    {
            if (timesIncorrect < 2)
      {
      CircuitPlayground.playTone(midi[45], 200);
      timesIncorrect++;
      }
      else
      {
      for(int p = 0; p < 10; p++)
      {
        CircuitPlayground.setPixelColor(p, 255, 0, 0);
      }
      CircuitPlayground.playTone(midi[55], 300);
      CircuitPlayground.playTone(midi[53], 300);
      CircuitPlayground.playTone(midi[51], 300);
      CircuitPlayground.playTone(midi[49], 500);
      while (resetButton == 0)
      {
      delay(10);
      }
    }
    leftButtonFlag = 0;
    }
    randomStationaryLED = random(0, 10);
   }
  leftButtonFlag = 0;
  resetButton = 0; 
  CirclingLED++;
    if(CirclingLED > 9)
  {
    CirclingLED = 0;
  }
  CircuitPlayground.clearPixels();
}


if(switchState)
{
  CircuitPlayground.setPixelColor(CirclingLED, 0, 255, 0);
  CircuitPlayground.setPixelColor(randomStationaryLED, 255, 0, 0);
  if(CirclingLED == randomStationaryLED)
  {
    CircuitPlayground.setPixelColor(CirclingLED, 0, 0, 255);
    CircuitPlayground.setPixelColor(randomStationaryLED, 0, 0, 255);
  }
    delay(circleDelayTime);
   if (leftButtonFlag == 1)
   {
     delay(10);
     if(CirclingLED == randomStationaryLED)
     {
      if (timesCorrect < 2)
      {
      circleDelayTime -=25;
      timesCorrect++;
      CircuitPlayground.playTone(midi[60], 200);
      }
      else
      {
        delay(10);
        for(int p = 0; p < 10; p++)
        {
          CircuitPlayground.setPixelColor(p, 0, 255, 0);
        }
      CircuitPlayground.playTone(midi[61], 230);
      CircuitPlayground.playTone(midi[64], 630);
        while (resetButton == 0)
        {
        delay(10);
        }
      }
    leftButtonFlag = 0;
    }
    if(CirclingLED != randomStationaryLED)
    {
            if (timesIncorrect < 2)
      {
      CircuitPlayground.playTone(midi[45], 200);
      timesIncorrect++;
      }
      else
      {
      for(int p = 0; p < 10; p++)
      {
        CircuitPlayground.setPixelColor(p, 255, 0, 0);
      }
      CircuitPlayground.playTone(midi[55], 300);
      CircuitPlayground.playTone(midi[53], 300);
      CircuitPlayground.playTone(midi[51], 300);
      CircuitPlayground.playTone(midi[49], 500);
      while (resetButton == 0)
      {
      delay(10);
      }
    }
    }
     randomStationaryLED = random(0, 10);
   }
  leftButtonFlag = 0;
  resetButton = 0; 
    CirclingLED++;
      if(CirclingLED > 9)
  {
    CirclingLED = 0;
  }
  CircuitPlayground.clearPixels();
  // randomStationaryLED = random(0, 10);
  // CircuitPlayground.setPixelColor(randomStationaryLED, 255, 0, 0);
}
}

void stopGreenLight(){
  leftButtonFlag = 1;
}

void differentMode(){
  flipSwitchFlag = 1;
}

void resetting(){
  rightButtonFlag = 1;
  resetButton = 1;
  timesCorrect = 0;
  timesIncorrect = 0;
  circleDelayTime = 200;
  score = 0;
}

void sparkleWhite()
{
int randomLED = random(10);
for(int i = 0; i < 3; i++)
{
  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(randomLED, 255, 255, 255);
  if(randomLED < 5)
  CircuitPlayground.setPixelColor(randomLED + 3, 255, 255, 255);
  if(randomLED > 5)
  CircuitPlayground.setPixelColor(randomLED - 4, 255, 255, 255);
  delay(30);
}
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
  }
}
