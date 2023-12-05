#include <Arduino.h>
#include "config.h"
#include "scheduler/Scheduler.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DetectionTask.h"
#include "tasks/GateControlTask.h"
#include "tasks/WashControlTask.h"
#include "tasks/SerialMonitorTask.h"

/*
/*this assignments has been done as a group by:
 Coli Alessandro: alessandro.coli2@studio.unibo.it
 Giangiulli Chiara: chiara.giangiulli@studio.unibo.it
 Pisoni Giovanni: giovanni.pisoni@studio.unibo.it
 Terenzi Mirco: mirco.terenzi@studio.unibo.it
 
 Link for the demonstration video: 
 https://liveunibo-my.sharepoint.com/:v:/g/personal/giovanni_pisoni_studio_unibo_it/EeLdtzAueyVKiL9ohLCltgoBZAEwALgI1wfhkAjFeqOyNg?nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJPbmVEcml2ZUZvckJ1c2luZXNzIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXciLCJyZWZlcnJhbFZpZXciOiJNeUZpbGVzTGlua0NvcHkifX0&e=5HOnat 
*/

Scheduler scheduler;
CarWasher* pCarWasher;
SerialMonitorTask* pSerialMonitor;


void setup() {
  scheduler.init(100);
  pCarWasher = new CarWasher();
  pCarWasher->init();
  
  pSerialMonitor = new SerialMonitorTask(pCarWasher);
  pSerialMonitor->init(100);

  BlinkingTask* pBlinkingTask = new BlinkingTask(LED02_PIN);
  pBlinkingTask->init(100);
  pBlinkingTask->setActive(false);

  DetectionTask* pDetectionTask = new DetectionTask(pCarWasher);
  pDetectionTask->init(500);  

  GateControlTask* pGateControlTask = new GateControlTask(pCarWasher, pBlinkingTask);
  pGateControlTask->init(500);

  WashControlTask* pWashControlTask = new WashControlTask(pCarWasher, pBlinkingTask, pSerialMonitor);
  pWashControlTask->init(1000);

  scheduler.addTask(pBlinkingTask);
  scheduler.addTask(pDetectionTask);
  scheduler.addTask(pGateControlTask);
  scheduler.addTask(pWashControlTask);
  scheduler.addTask(pSerialMonitor);

}

void loop() {
  scheduler.schedule();
}