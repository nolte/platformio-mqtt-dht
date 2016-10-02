#include "Arduino.h"
#include "DeepSleep.h"

LoopDeepSleep::LoopDeepSleep(int delayTime)
{
	_delayTime = delayTime * 1000;
	_previousMillis = 0;
}

bool LoopDeepSleep::isActive()
{
	unsigned long currentMillis = millis();
	if(currentMillis - _previousMillis >= _delayTime) {
	    // save the last time you blinked the LED
	    #if DEBUG
			Serial.println("is active ...");
			Serial.print("Current:");	
			Serial.print(currentMillis);
			Serial.print(" prev:");
			Serial.println(_previousMillis);
		#endif	
	  	_previousMillis = currentMillis;
	    // set the LED with the ledState of the variable:
		return true;
	}
	return false;

}

void LoopDeepSleep::sleep()
{
	delay(1);
}
