#include "Arduino.h"

class DeepSleep
{
	public:
	  	virtual ~DeepSleep() {};
	  	virtual void sleep() = 0;
	  	virtual bool isActive();
	private:
		int _delayTime;
};


class DelayDeepSleep : public DeepSleep {
	public:
	    DelayDeepSleep(int delayTime);
		virtual void sleep();
	private:
		int _delayTime;	
};

class LoopDeepSleep : public DeepSleep {
	public:
	    LoopDeepSleep(int delayTime);
		virtual void sleep();
		virtual bool isActive();
	private:
		int _delayTime;	
		unsigned long _previousMillis;
};

#ifdef ESPSLEEP
class ESPDeepSleep : public DeepSleep {
	public:
	    ESPDeepSleep(int delayTime);
		virtual void sleep();
	private:
		int _delayTime;	
};
#endif	
