#include "rc_utils.h"
#include <Arduino.h>

#define CH1 2 // Steering wheel
#define CH2 3 // Accelerator
#define CH3 4 // Handle button
#define CH4 5 // Handle switch
#define CH5 6 // CH5 button
#define CH6 7 // CH6 button

int ch1Value, ch2Value, ch3Value, ch4Value, ch5Value, ch6Value;
// bool ch5Value, ch6Value;

void rcSetup(){
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
}

bool isRadioEnabled(){
  // TODO: complete code
  return true;
}

bool rcReadisBraking(){
  // TODO: complete code
  return false;
}

bool rcIsDirectionForward(){
  // TODO: complete code
  return true;
}

int rcReadAccValue(){
  // TODO: complete code
  return 0;
}

int rcReadLimitValue(){
  // TODO: complete code
  return 100;
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
  ch1Value = readChannel(CH1, -100, 100, 0);
  ch2Value = readChannel(CH2, -100, 100, 0);
  ch3Value = readChannel(CH3, -100, 100, 0);
  ch4Value = readChannel(CH4, -100, 100, 0);
  ch5Value = readChannel(CH5, -100, 100, 0);
  ch6Value = readChannel(CH6, -100, 100, 0);
  // ch5Value = readSwitch(CH5, false);
  // ch6Value = readSwitch(CH6, false);
  
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" Ch4: ");
  Serial.print(ch4Value);
  Serial.print(" Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" Ch6: ");
  Serial.println(ch6Value);
  delay(50);
}