#ifndef MqttDHT_h
#define MqttDHT_h
#include <MqttManager.h>
#include <DHT.h>
#include "Arduino.h"

class MqttDHT
{
	public:
	  MqttDHT(const char* mqtt_topic,char* device_id,uint8_t pin,uint8_t type);
	  bool readSensor(MqttManager& mqttManager);
	  void begin();
	private:
	  const char* _mqtt_topic;
	  char* _device_id;
	  int _pin;
	  uint8_t _type;
	  DHT _dht = DHT(_pin, _type, 50);
};

#endif
