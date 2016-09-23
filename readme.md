# Temperature MQTT Sensor
[![Build Status](https://travis-ci.org/nolte/platformio-mqtt-dht.svg?branch=master)](https://travis-ci.org/nolte/platformio-mqtt-dht)  

Publish the DHT Information all minute to a central MQTT topic `/iot/dht`, after than the NodeMCU go in the DeepSleep mode.

```json
{"humidity":32.20,"temperature":24.20,"heat_index":23.52,"device_id":"dht-livingroom"}
```

## Schaltung

<img src="doc/schematic_bb.png" alt="breadboard" width="250" />

## Hardware

 - NodeMCU Deleloper Board
 - DHT22
 - 10kΩ
