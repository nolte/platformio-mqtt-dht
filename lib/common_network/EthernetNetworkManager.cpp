#ifdef ETH

#include "Arduino.h"
#include "NetworkManager.h"
#include <PubSubClient.h>

#include <SPI.h>
#include <Ethernet.h>
#include <Client.h>

EthernetNetworkManager::EthernetNetworkManager()
{
		// MAC Adresse des Ethernet Shields
		EthernetClient client;
		byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xAF };
		// Device IP Address
		IPAddress ip(192, 168, 178, 5);
		_ip = ip;
		_mac = mac;
		_client = client;
}

IPAddress EthernetNetworkManager::getIp()
{
return _ip;
}

EthernetClient& EthernetNetworkManager::getClient()
{
return _client;
}

void EthernetNetworkManager::disconnect() {
	#if DEBUG
		Serial.println("disconnect network ..");
	#endif
	delay(100);
}	

void EthernetNetworkManager::begin() {
	Ethernet.begin(_mac, getIp());
	#if DEBUG
		Serial.println("start Ethernet");
		Serial.print("IP:");
		Serial.println(getIp());
	#endif
	delay(1000);
}	

#endif