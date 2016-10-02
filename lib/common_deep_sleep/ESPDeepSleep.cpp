#ifdef ESPSLEEP

#include "Arduino.h"
#include "DeepSleep.h"

ESPDeepSleep::ESPDeepSleep(int delayTime)
{
	_delayTime = delayTime * 1000000;
}

void ESPDeepSleep::sleep()
{
	#if DEBUG
		Serial.println("esp deepsleep start ...");
	#endif
	ESP.deepSleep(_delayTime , WAKE_RF_DEFAULT);
	delay(200);
}

#endif