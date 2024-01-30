#include <Arduino.h>
#include <task.h>
#include "tasks.h"
#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  50

double waterLevel;

/* wifi network info */

const char* ssid = "";
const char* password = "";

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* topic1 = "water_level";
const char* topic2 = "frequency";

/* MQTT client management */

/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);


unsigned long lastMsgTime = 0;
char msg1[MSG_BUFFER_SIZE];


TaskHandle_t Task1;

void setup_wifi() {

  delay(10);

  Serial.println(String("Connecting to ") + ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* MQTT subscribing callback */

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

void reconnect() {
  
  // Loop until we're reconnected
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
    
    Serial.begin(115200); 
    setup_wifi();
    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    xTaskCreatePinnedToCore(tasks::monitoringTask,"Task1",10000,NULL,1,&Task1,0);                         


}

void loop() {
    if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > 10000) {
    lastMsgTime = now;

    /* creating a msg in the buffer */
    snprintf (msg1, MSG_BUFFER_SIZE, "water level: %d", waterLevel);

    Serial.println(String("Publishing message: ") + msg1);
    
    /* publishing the msg */
    client.publish(topic1, msg1);  
  }
}
