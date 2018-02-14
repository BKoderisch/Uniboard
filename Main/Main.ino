/**
* this programm is the standard Uniboard programm. 
* It publish the sensor Values of an analog sensor to a mqtt server.
*
* @author Benjamin Koderisch
* @version 1.0 17.11.17
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <StatusLed.h>
#include <AnalogTemp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#define mqtt_server "52.58.176.229"
#define sensor_topic "server/test"

// create objects
AnalogTemp tempSensor(0);
StatusLed statusLed(10);
WiFiClient espClient;
PubSubClient client(espClient);

// create local variables
long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 1.0;
int ledPin = 15;

/**
* Functions will be called when the connection is lost
*/
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // blink 5 times very fast
      statusLed.blink(5, 50);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**
* handle arrived messages
*
* @param topic describes the topic of the arrived message
* @param payload contains the data
* @param length amount of chars in the message
*/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message = "";
  for (int i=0;i<length;i++) {
    message = message + (char)payload[i];
    Serial.print((char)payload[i]);
  }
  Serial.println();

  Serial.println(message);
  if(message.equals("on")){
    digitalWrite(ledPin, HIGH);
    Serial.println("an");
  } else if (message.equals("off")){
    digitalWrite(ledPin, LOW);
    Serial.println("aus");
  }
}

/**
* Fist function that is called by the program.
* Contains initialisations
*/
void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  client.setServer(mqtt_server, 1883);  
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
}

/**
* Main function that loops until death.
*/
void loop() {
  // make shure that the client is connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // after 10 seconds
  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    // read the analog temperature sensor
    float temp = tempSensor.readTemp();

    // publish the value of the temperature sensor
    client.publish(sensor_topic, String(temp).c_str(), true);
    // blink fast two times
    statusLed.blink(2,200);
  }
}
