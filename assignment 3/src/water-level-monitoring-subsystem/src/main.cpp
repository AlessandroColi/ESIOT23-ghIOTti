#include <Arduino.h>
#include <task.h>
#include "tasks.h"



void setup() {

    TaskHandle_t Task1;
    Serial.begin(115200); 

    xTaskCreatePinnedToCore(tasks::monitoringTask,"Task1",10000,NULL,1,&Task1,0);                         


}

void loop() {
}
