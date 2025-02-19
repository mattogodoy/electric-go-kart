#include "pins.h"
#include "manual_control.h"
#include <Arduino.h>

int manualAccelValue = 0;
int manualBrakeValue = 0;
int manualLimitValue = 100;
bool manualDirectionValue = true;

void manualSetup(){
  pinMode(PIN_INPUT_MAN_ACCEL, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_BRAKE, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_LIMIT, INPUT); // Add pulldown resistor to this pin
  pinMode(PIN_INPUT_MAN_DIREC, INPUT_PULLUP);
}

bool manualIsBraking(){
  // Braking happens with an analog pedal, but the motor controller
  // only accepts a boolean value for braking. We consider we're
  // braking when the pedal is pressed 40% or more.
  // Pedals have an input range from 170 to 670
  int value = map(manualBrakeValue, 170, 670, 0, 100);
  return (value > 40);
}

bool manualIsDirectionForward(){
  // We use a manual switch for this
  return manualDirectionValue;
}

int manualReadAccValue(){
  // Pedals have an input range from 170 to 670
  int value = map(manualAccelValue, 170, 670, 0, 100);

  // Apply accelerator limits
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
