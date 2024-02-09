#include <Arduino.h>
#include <task.h>
#include "tasksImpl.h"
#include <WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  50


double waterLevel;
bool working;
long updateFrequence;

/* wifi network info */

const char* ssid = "";
const char* password = "";

/* MQTT server address */
const char* mqtt_server = "test.mosquitto.org";

/* MQTT topic */
const char* backend = "backend";
const char* esp = "esp32";

/* MQTT client management */

/* MQTT client management */

WiFiClient espClient;
PubSubClient client(espClient);


unsigned long lastMsgTime = 0;
char msg1[MSG_BUFFER_SIZE];


TaskHandle_t Task1;
TaskHandle_t Task2;

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
  memcpy(&updateFrequence, payload, sizeof(long));
}

/* generate mqttTopic */
char* toTopics(const char* source, const char* destination) {
    // Calculate the length of the resulting string
    size_t length = strlen("RiverMonitoring/") + strlen(source) + strlen("/") + strlen(destination) + 1;

    // Allocate memory for the resulting string
    char* result = (char*)malloc(length);

    // Check for allocation failure
    if (result == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Construct the resulting string
    snprintf(result, length, "RiverMonitoring/%s/%s", source, destination);

    return result;
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
      client.subscribe("RiverMonitoring/+/+"); //subscribe to all topics related to this project
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

    xTaskCreatePinnedToCore(tasksImpl::monitoringTask,"Task1",10000,NULL,1,&Task1,0);
    xTaskCreatePinnedToCore(tasksImpl::ledControlTask,"Task2",10000,NULL,1,&Task2,0);
}

void loop() {

    if (WiFi.status() == WL_CONNECTED && client.connected()) {
        working = true;
    } else {
        working = false;
    }

    if (!client.connected()) {
        reconnect();
    }
    client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > 10000) {
    lastMsgTime = now;

    /* creating a msg in the buffer */
    char wl[50];
    dtostrf(waterLevel,10,2,wl);
    snprintf (msg1, MSG_BUFFER_SIZE, wl);

    Serial.println(String("Publishing message: ") + msg1);
    
    /* publishing the msg */
    client.publish(toTopics(esp,backend), msg1);  
  }
}

