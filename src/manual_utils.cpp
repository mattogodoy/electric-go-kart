#include "manual_utils.h"
#include <Arduino.h>

const int potPin = A0; // Speed limiter
const int accPin = A1; // Accelerator
const int brakePin = A2; // Brake

void manualSetup(){
  pinMode(potPin, INPUT);
  pinMode(accPin, INPUT);
  pinMode(brakePin, INPUT);
}

bool manualReadIsBraking(){
  // TODO: complete code
  return false;
}

bool manualReadIsDirectionForward(){
  // TODO: complete code
  return true;
}

int manualReadAccValue(){
  // TODO: Calibrate and map values
  return analogRead(accPin);
}

int manualReadLimitValue(){
  // TODO: Calibrate and map values
  return analogRead(potPin);
}
