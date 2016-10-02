#include "Arduino.h"
#include "DeepSleep.h"

DelayDeepSleep::DelayDeepSleep(int delayTime)
{
	_delayTime = delayTime * 1000 ;
}

void DelayDeepSleep::sleep()
{
	#if DEBUG
		Serial.println("delay deepsleep start ...");
	#endif
	delay(_delayTime );
}
