#include <Arduino.h>

void rcSetup();
bool rcIsOverrideEnabled();
bool rcIsBraking();
bool rcIsDirectionForward();
int rcReadAccValue();
int rcReadLimitValue();
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue);
bool readSwitch(byte channelInput, bool defaultValue);
void rcUpdateValues();
void rcDebug();