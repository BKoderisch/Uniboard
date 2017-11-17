/**
* this programm is the standard Uniboard programm. 
* It publish the sensor Values of a analog sensor to a mqtt server.
*
* @author Benjamin Koderisch
* @version 1.0 17.11.17
*/

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <StatusLed.h>
#include <AnalogTemp.h>

#define wifi_ssid "Zandi"
#define wifi_password "22627898426324258151"
#define mqtt_server "192.168.178.49"
#define sensor_topic "sensorNode1/temperature"

AnalogTemp tempSensor(0);
StatusLed statusLed(2);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

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
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
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

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);  
}

long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 1.0;

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
