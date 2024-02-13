#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <ezButton.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"  

Adafruit_7segment matrix = Adafruit_7segment(); 
ezButton button(2); 
  
  unsigned long prevTime = millis(), prevTimeS = millis();
  long stop = 420000, seconds = 1000;
  int min = 0, sec = 0;

  bool press = false;
  bool reset = false;
  bool drawDots = true;


void printTime() {

  if (press){
    
    int time = (min * 100) + sec;

    matrix.println(time, DEC);


  }
  else {
    matrix.println("0000");
    matrix.writeDisplay();
    }

  if (sec == 0) reset = true;

  if (sec == 0 && min == 0) {

    digitalWrite(4, LOW);
    press = false;

  }

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  matrix.begin(0x70);
  
  button.setDebounceTime(50);
  pinMode(4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long time = millis();

  button.loop();

  matrix.drawColon(drawDots);
  
  if (min < 10) {
  
    matrix.writeDigitNum(0, 0);

    if (min == 0) matrix.writeDigitNum(1,0);
    if (sec < 10) matrix.writeDigitNum(3, 0);

  }

  if (button.isPressed()) {

    digitalWrite(4, HIGH);
    prevTime = millis();
    press = true;
    min = min + 7;
    reset = false;

  }

  if (time - prevTimeS > seconds && (press == true)) {

    if (reset){

      sec = 60;
      min--;
      reset = false;

    }
    sec--;

    if (sec < 0) sec = 0;

    prevTimeS = time;

    matrix.writeDisplay();

  }

  printTime();

}
