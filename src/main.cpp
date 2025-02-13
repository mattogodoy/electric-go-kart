#include "rc_utils.h"
#include "manual_utils.h"
#include <Arduino.h>

unsigned int accLimit = 0; // 0-100
unsigned int accValue = 0; // 0-100
bool isBraking = false;
bool isDirectionForward = true;


void setup() {
  Serial.begin(115200);
}

void applyBrakes(){
  // TODO: Complete code
}

void setDirection(bool isDirectionForward){
  // TODO: Complete code
}

void setAcceleration(int value){
  // TODO: Complete code
}

void process(){
  // TODO: Move variables outside
  bool isBraking = false;
  bool isDirectionForward = true;
  int accValue = 0; // 0-100
  int accLimit = 0; // 0-100

  if(isRadioEnabled()){
    // === REMOTE CONTROL ===
    // Use the values coming from the RC emitter
    isBraking = rcReadisBraking();
    isDirectionForward = rcIsDirectionForward();
    accValue = rcReadAccValue();
    accLimit = rcReadLimitValue();
  } else {
    // === MANUAL CONTROL ===
    // Use the values from the kart's controls
    isBraking = manualReadIsBraking();
    isDirectionForward = manualReadIsDirectionForward();
    accValue = manualReadAccValue();
    accLimit = manualReadLimitValue();
  }

  // === APPLY VALUES ===
  // Brakes
  if(isBraking){
    applyBrakes();
  }

  // Direction
  setDirection(isDirectionForward);
  
  // Accelerator
  if(accValue > accLimit){
    accValue = accLimit;
  }
  setAcceleration(accValue);
}

void loop() {
  rcUpdateValues();
}
