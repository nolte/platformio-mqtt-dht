
#include <ArduinoJson.h>

#include <PubSubClient.h>
#include <DHT.h>

#include <NetworkManager.h>
#include <MqttManager.h>
#include <MqttDeviceAlliveMessage.h>
#include <MqttDHT.h>

#include <DeepSleep.h>

#ifdef WIFI
	ESP8266NetworkManager networkManager;
#endif
	
#ifdef ETH
	EthernetNetworkManager networkManager;
#endif	


#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif
	

char DEVICE_ID[] = MQTT_DEVICE_ID;

MqttManager mqttManager(MQTT_DEVICE_ID,MQTT_HOST,networkManager.getClient());

char MQTT_DHT_PATH[] = "/iot/dht";
char MQTT_A_LIVE_PATH[] = "/iot/devices";

const char *features[] = { "humidity","temp","heat_index" };
MqttDeviceAlliveMessage aliveMessage(mqttManager.getClient(),MQTT_A_LIVE_PATH,DEVICE_ID,features, ARRAY_SIZE(features));



#ifdef ESPSLEEP
	ESPDeepSleep deepSleep(UPDATEINTERVALL);
#endif	
	
#ifndef ESPSLEEP	
	LoopDeepSleep deepSleep(UPDATEINTERVALL);
#endif		
	


MqttDHT mqttDHT(MQTT_DHT_PATH,DEVICE_ID,DHTPIN,DHTTYPE);
		
void setup() {
	#if DEBUG
		Serial.begin(9600);
		Serial.println("start int DHT Sensor");
	#endif
		
	networkManager.begin();
	delay(2500);
	mqttManager.begin();
	delay(1000);
	mqttDHT.begin();
	#if DEBUG
		Serial.println("end int DHT Sensor");
	#endif		
}


void loop() {
	// Wait a few seconds between measurements.
	if (deepSleep.isActive()) {
	
	#if DEBUG
		Serial.println("intervall start");
	#endif	
	bool running = false;
	
	mqttManager.checkOrReconnect();
	delay(100);
	mqttManager.loop();
	
	running = mqttDHT.readSensor(mqttManager);
	aliveMessage.sendAliveMessage(networkManager.getIp(),running);
	
	mqttManager.disconnect();
	
	networkManager.disconnect();
	}
	
	deepSleep.sleep();
}
