#include "pins.h"
#include "rc_control.h"
#include <Arduino.h>

// === Radio channels map ===
// CH1 = Steering wheel
// CH2 = Accelerator
// CH3 = Handle button
// CH4 = Handle 3 way switch
// CH5 = CH5 button
// CH6 = CH6 button

int rcAccelValue = 0;
int rcLimitValue = 100;
bool rcDirectionValue = true;
bool rcOverrideValue = false;

void rcSetup(){
  pinMode(PIN_INPUT_RC_ACCEL, INPUT);
  pinMode(PIN_INPUT_RC_DIREC, INPUT_PULLUP);
  pinMode(PIN_INPUT_RC_OVERR, INPUT);
  pinMode(PIN_INPUT_RC_LIMIT, INPUT);
}

bool rcIsOverrideEnabled(){
  return rcOverrideValue;
}

bool rcIsBraking(){
  if(rcAccelValue < -50)
    return true;
  else
    return false;
}

bool rcIsDirectionForward(){
  return rcDirectionValue;
}

int rcReadAccValue(){
  // The same channel is used for accelerating and braking.
  // Ignore inputs when braking
  if(rcAccelValue < 0) return 0;

  // Apply accelerator limits
  return (rcAccelValue > rcReadLimitValue()) ? rcReadLimitValue() : rcAccelValue;
}

int rcReadLimitValue(){
  if(rcLimitValue < -50){ // Switch in position 0
    return 30;
  } else if(rcLimitValue > 50){ // Switch in position 2
    return 100;
  } else { // Switch in position 1
    return 60;
  }
}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void rcUpdateValues() {
  rcAccelValue = readChannel(PIN_INPUT_RC_ACCEL, -100, 100, 0);
  rcLimitValue = readChannel(PIN_INPUT_RC_LIMIT, -100, 100, 0);
  rcDirectionValue = !readSwitch(PIN_INPUT_RC_DIREC, true); // This value is negated becaues it starts low
  rcOverrideValue =  readSwitch(PIN_INPUT_RC_OVERR, false);
}

void rcDebug(){
  Serial.print("RC MODE - Acc: ");
  Serial.print("[" + String(rcAccelValue) + "] ");
  Serial.print(rcReadAccValue());
  Serial.print(" - Limit: ");
  Serial.print("[" + String(rcLimitValue) + "] ");
  Serial.print(rcReadLimitValue());
  Serial.print(" - isBraking: ");
  Serial.print("[" + String(rcAccelValue) + "] ");
  Serial.print(rcIsBraking());
  Serial.print(" - isDirForward: ");
  Serial.print(rcIsDirectionForward());
  Serial.print(" - isOverrideOn: ");
  Serial.println(rcIsOverrideEnabled());
}
