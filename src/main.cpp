#include "pins.h"
#include "rc_control.h"
#include "manual_control.h"
#include <Arduino.h>

// Debugging options for the serial monitor
#define INPUT_DEBUG false
#define OUTPUT_DEBUG false

unsigned int accLimit = 0; // 0-100
unsigned int accValue = 0; // 0-100
bool isBraking = false;
bool isDirectionForward = true;

void setup() {
  // Enable serial communication for debugging
  if(INPUT_DEBUG || OUTPUT_DEBUG) Serial.begin(115200);

  // Initialize control modules
  manualSetup();
  rcSetup();

  // Initialize output pins
  pinMode(PIN_OUTPUT_ACCEL, OUTPUT);
  pinMode(PIN_OUTPUT_BRAKE, OUTPUT);
  pinMode(PIN_OUTPUT_DIREC, OUTPUT);
}

void setBrakes(bool isBraking){
  if(isBraking)
    digitalWrite(PIN_OUTPUT_BRAKE, HIGH);
  else
    digitalWrite(PIN_OUTPUT_BRAKE, LOW);
}

void setDirection(bool isDirectionForward){
  if(isDirectionForward)
    digitalWrite(PIN_OUTPUT_DIREC, HIGH);
  else
    digitalWrite(PIN_OUTPUT_DIREC, LOW);
}

void setAcceleration(int pwmValue){
  // PWM value: 0-255 -> 0%-100%
  analogWrite(PIN_OUTPUT_ACCEL, pwmValue);
}

void outputDebug(){
  Serial.print("OUTPUT - Mode: ");
  Serial.print(rcIsOverrideEnabled() ? "RC" : "MANUAL");
  Serial.print(" Acc: ");
  Serial.print(accValue);
  Serial.print(" Limit: ");
  Serial.print(accLimit);
  Serial.print(" isBraking: ");
  Serial.print(isBraking);
  Serial.print(" isDirForward: ");
  Serial.println(isDirectionForward);
}

void loop(){  
  // Read input values for both modes
  rcUpdateValues();
  manualUpdateValues();

  if(rcIsOverrideEnabled()){
    // === REMOTE CONTROL ===
    // Use the values coming from the RC emitter
    isBraking = manualIsBraking() || rcIsBraking(); // Allow manual brake override when on RC mode
    isDirectionForward = rcIsDirectionForward();
    accValue = rcReadAccValue();
    accLimit = rcReadLimitValue();
    if(INPUT_DEBUG) rcDebug();
  } else {
    // === MANUAL CONTROL ===
    // Use the values from the kart's controls
    isBraking = manualIsBraking();
    isDirectionForward = manualIsDirectionForward();
    accValue = manualReadAccValue();
    accLimit = manualReadLimitValue();
    if(INPUT_DEBUG) manualDebug();
  }

  if(OUTPUT_DEBUG) outputDebug();

  // === APPLY VALUES ===
  // Brakes
  setBrakes(isBraking);

  // Direction
  setDirection(isDirectionForward);
  
  // Accelerator
  setAcceleration(accValue);
}
