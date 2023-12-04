#include <Arduino.h>
#include "config.h"
#include "scheduler/Scheduler.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DetectionTask.h"
#include "tasks/GateControlTask.h"
#include "tasks/WashControlTask.h"
#include "SerialMonitor.h"

Scheduler scheduler;
CarWasher* pCarWasher;
SerialMonitor* pSerialMonitor;


void setup() {
  scheduler.init(10);
  pCarWasher = new CarWasher();
  pCarWasher->init();
  
  pSerialMonitor = new SerialMonitor(pCarWasher);
  pSerialMonitor->init();

  BlinkingTask* pBlinkingTask = new BlinkingTask(LED02_PIN);
  pBlinkingTask->init(10);
  pBlinkingTask->setActive(false);

  DetectionTask* pDetectionTask = new DetectionTask(pCarWasher);
  pDetectionTask->init(50);  

  GateControlTask* pGateControlTask = new GateControlTask(pCarWasher, pBlinkingTask);
  pGateControlTask->init(500);

  WashControlTask* pWashControlTask = new WashControlTask(pCarWasher, pBlinkingTask, pSerialMonitor);
  pWashControlTask->init(1000);

  scheduler.addTask(pBlinkingTask);
  scheduler.addTask(pDetectionTask);
  scheduler.addTask(pGateControlTask);
  scheduler.addTask(pWashControlTask);

}

void loop() {
  scheduler.schedule();
  pSerialMonitor->update();
}