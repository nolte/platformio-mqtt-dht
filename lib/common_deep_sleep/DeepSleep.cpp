#include "Arduino.h"
#include "DeepSleep.h"

bool DeepSleep::isActive()
{
	#if DEBUG
		Serial.println("check deep sleep is Active ...");
	#endif
	return true;
}