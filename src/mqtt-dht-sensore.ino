// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#include "DHT.h"
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MqttDeviceAlliveMessage.h>

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

//controll led 
#define WLANLED 4 

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

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
DHT dht(DHTPIN, DHTTYPE, 50);

// MQTT Config

WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = WLAN_SSID;
const char* password = WLAN_PASSWORD;

char DEVICE_ID[] = MQTT_DEVICE_ID;

// IP des MQTT Servers
const char* mqtt_server = MQTT_HOST;

char MQTT_DHT_PATH[] = "/iot/dht";
char MQTT_A_LIVE_PATH[] = "/iot/devices";

const char *features[] = { "humidity","temperature","heat_index" };
MqttDeviceAlliveMessage aliveMessage(client,MQTT_A_LIVE_PATH,DEVICE_ID,features, ARRAY_SIZE(features));

#define SLEEP_DELAY_IN_SECONDS  60

#define WIFI_SLEEP_DELAY_IN_SECONDS  120


long wifiretrycount = 0;

long lastMsg = 0;

void setup() {
	Serial.begin(9600);
	Serial.println("DHTxx test!");
	 pinMode(WLANLED, OUTPUT);
	setup_wifi();
	client.setServer(mqtt_server, 1883);
	// client.setCallback(callback);

	dht.begin();
}

void setup_wifi() {
	digitalWrite(WLANLED, HIGH);
	
	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	
	WiFi.begin(ssid, password);
	wifiretrycount = 0;
			
	while (WiFi.status() != WL_CONNECTED && wifiretrycount < 500) {
		delay(500);
		Serial.print(".");
		wifiretrycount ++;
		digitalWrite(WLANLED, HIGH);
	}
	
	if(WiFi.status() != WL_CONNECTED && wifiretrycount >= 500 )
	{
		ESP.deepSleep(WIFI_SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
		Serial.println("Faild connect to the Wlan go to the deepSleep and retry");
		delay(100);
	}
	digitalWrite(WLANLED, LOW);

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(DEVICE_ID)) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			
			// ... and resubscribe
			//client.subscribe("inTopic");
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void loop() {
	// Wait a few seconds between measurements.
	boolean running = false;
	if (!client.connected()) {
		reconnect();
	}
	client.loop();
	delay(2000);
	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	
	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t)) {
		Serial.println("Failed to read from DHT sensor!");
		
	} else {
		running = true;
		// Compute heat index in Celsius (isFahreheit = false)
		float hic = dht.computeHeatIndex(t, h, false);

		String json;
		StaticJsonBuffer < 200 > jsonBuffer;
		JsonObject& root = jsonBuffer.createObject();
		root["humidity"] = h;
		root["temperature"] = t;
		root["heat_index"] = hic;
		root["device_id"] = DEVICE_ID;
		String jsonString = "";
		root.printTo(jsonString);

		Serial.print(jsonString);
		Serial.print("\n");

		int commandLen = jsonString.length() + 1;
		char message_buffCommand[commandLen];
		jsonString.toCharArray(message_buffCommand, commandLen);

		client.publish(MQTT_DHT_PATH, message_buffCommand);
	}
	aliveMessage.sendAliveMessage(WiFi.localIP(),running);
	delay(100);
	
	Serial.println("Closing MQTT connection...");
	client.disconnect();
	delay(100);
	Serial.println("Closing WiFi connection...");
	WiFi.disconnect();
	delay(100);

	ESP.deepSleep(SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
	delay(100);

}
