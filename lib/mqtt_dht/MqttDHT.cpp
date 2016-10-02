
#include "Arduino.h"
#include <DHT.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "MqttDHT.h"
#include "MqttManager.h"

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.

MqttDHT::MqttDHT(const char* mqtt_topic,char* device_id, uint8_t pin,uint8_t type)
{
  _mqtt_topic = mqtt_topic;
  _device_id = device_id;
  DHT dht(pin,type,50);
  _pin = pin;
  _type = type;
  _dht = dht;
 
}

bool MqttDHT::readSensor(MqttManager& mqttManager)
{
	delay(10);
	bool running = false;
	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = _dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = _dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	
	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		#if DEBUG
			Serial.println("Failed to read from DHT sensor!");
		#endif
		
	} else {
		running = true;
		// Compute heat index in Celsius (isFahreheit = false)
		float hic = _dht.computeHeatIndex(t, h, false);

		String json;
		StaticJsonBuffer < 220 > jsonBuffer;
		JsonObject& root = jsonBuffer.createObject();
		root["humidity"] = h;
		root["temperature"] = t;
		root["heat_index"] = hic;
		root["device_id"] = _device_id;
		root["pin"] = _pin;
		String jsonString = "";
		root.printTo(jsonString);
		#if DEBUG
			Serial.print(jsonString);
			Serial.print("\n");
		#endif 
		int commandLen = jsonString.length() + 1;
		char message_buffCommand[commandLen];
		jsonString.toCharArray(message_buffCommand, commandLen);

		mqttManager.publish(_mqtt_topic, message_buffCommand);
	}

 return running;
}
void MqttDHT::begin()
{
 _dht.begin();
}