#include <Arduino.h>

void rcSetup();
bool isRadioEnabled();
bool rcReadisBraking();
bool rcIsDirectionForward();
int rcReadAccValue();
int rcReadLimitValue();
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue);
bool readSwitch(byte channelInput, bool defaultValue);
void rcUpdateValues();
