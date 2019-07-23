/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 30

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// All the wires needed for full functionality
#define DIR 8
#define STEP 9                         
//Uncomment line to use enable/disable functionality
#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  stepper.setEnableActiveState(LOW);
  Serial.print("Waiting");
  pinMode(11,INPUT_PULLUP);
  stepper.setMicrostep(16);
}

int sign = 1;
bool moved = false;
void loop() {
    while(!digitalRead(11)){
      if(!moved){
        stepper.enable();
        //Direction Posting
        if(sign>0)Serial.print("\nForward Rotations: ");
        else Serial.print("\nBackward Rotations: ");
      }
      stepper.rotate(sign*360);
      Serial.print("| ");
      moved=true;
    }
    if(moved){
      moved=false;
      stepper.disable();
      sign*=-1;
      Serial.print("\nWaiting");
    }
    Serial.print(".");
    delay(500);
}
