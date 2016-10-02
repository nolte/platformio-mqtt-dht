# Temperature MQTT Sensor
[![Build Status](https://travis-ci.org/nolte/platformio-mqtt-dht.svg?branch=master)](https://travis-ci.org/nolte/platformio-mqtt-dht)  

Publish the DHT Information all minute to a central MQTT topic `/iot/dht`, after than the NodeMCU go in the DeepSleep mode.

```json
{"humidity":32.20,"temperature":24.20,"heat_index":23.52,"device_id":"dht-livingroom","pin":2}
```

## Schaltung

<img src="doc/schematic_bb.png" alt="breadboard" width="250" />

## Build Parameter

 The different Hardware combinations can be controlled with build parameters from the `platformio.ini`.


### Common Parameters

 -DDEBUG 
 -DDHTPIN=2 
 -DDHTTYPE=DHT11 
 -DUPDATEINTERVALL=30
 '-DMQTT_DEVICE_ID="dht-livingroom-node"' 
 '-DMQTT_HOST="maxchen"'  

### NodeMCU Parameters

 '-DWLAN_SSID="{{WLAN SSID}}"' 
 '-DWLAN_PASSWORD="{{WLAN PASSWORD}}"' 
 -DESPSLEEP 
 -DWIFI 

### Arduino Parameters

 -DETH

## Hardware
 

### NodeMCU Setup
 - [NodeMCU](http://nodemcu.com/index_en.html) Deleloper Board 
 - DHT22
 - 10kΩ
 
### ArduinoNetwork Setup
 - [Arduino Uno](https://www.arduino.cc/en/Main/ArduinoBoardUno)
 - [Ethernet Shield](https://www.arduino.cc/en/Main/ArduinoEthernetShield)
 - DHT22
 - 10kΩ
 
# Libs
 - [DHT Sensor Library](http://platformio.org/lib/show/19/DHT%20sensor%20library)
 - [Arduino Json](http://platformio.org/lib/show/64/ArduinoJson)   
 - [MQTT PubSubClient](http://platformio.org/lib/show/89/PubSubClient)
 - [MQTT AliveMessage](http://platformio.org/lib/show/365/MQTT%20Device%20Alive) 
 
