#include "pins.h"
#include "manual_control.h"
#include <Arduino.h>

int manualAccelValue = 0;
int manualBrakeValue = 0;
int manualLimitValue = 100;
bool manualDirectionValue = true;

// Pedals have an input range from ~200 to ~600
int minPedalValue = 200;
int maxPedalValue = 600:

void manualSetup(){
  pinMode(PIN_INPUT_MAN_ACCEL, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_BRAKE, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_LIMIT, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_DIREC, INPUT_PULLUP);
}

int mapPedalValue(int value){
  // Translate the pedal inputs to a value from 0 to 100.

  // The map function returns funky values if you give it
  // values lower than the minimum or higher than the maximum,
  // so we limit them.
  if(value < minPedalValue)
    value = minPedalValue;

  if(value > maxPedalValue)
    value = maxPedalValue;

  return map(value, minPedalValue, maxPedalValue, 0, 100);
}

bool manualIsBraking(){
  int value = mapPedalValue(manualBrakeValue);

  // Braking happens with an analog pedal, but the motor controller
  // only accepts a boolean value for braking. We consider we're
  // braking when the pedal is pressed 40% or more.
  return (value > 40);
}

bool manualIsDirectionForward(){
  // We use a manual switch for this
  return manualDirectionValue;
}

int manualReadAccValue(){
  int value = mapPedalValue(manualAccelValue);

  // Apply acceleration limits
  return (value > manualReadLimitValue()) ? manualReadLimitValue() : value;
}

int manualReadLimitValue(){
  // Limit potentiomenter has an input range from 0 to 848
  return map(manualLimitValue, 0, 848, 0, 100);
}

void manualUpdateValues() {
  manualAccelValue = analogRead(PIN_INPUT_MAN_ACCEL);
  manualBrakeValue = analogRead(PIN_INPUT_MAN_BRAKE);
  manualLimitValue = analogRead(PIN_INPUT_MAN_LIMIT);
  manualDirectionValue = digitalRead(PIN_INPUT_MAN_DIREC);
}

void manualDebug(){
  Serial.print("MANUAL MODE - Acc: ");
  Serial.print("[" + String(manualAccelValue) + "] ");
  Serial.print(manualReadAccValue());
  Serial.print(" - Limit: ");
  Serial.print("[" + String(manualLimitValue) + "] ");
  Serial.print(manualReadLimitValue());
  Serial.print(" - isBraking: ");
  Serial.print("[" + String(manualBrakeValue) + "] ");
  Serial.print(manualIsBraking());
  Serial.print(" - isDirForward: ");
  Serial.println(manualIsDirectionForward());
}
