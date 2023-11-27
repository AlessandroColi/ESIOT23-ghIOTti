#include <Arduino.h>
#include "config.h"
#include "scheduler/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DetectionTask.h"
#include "tasks/GateControlTask.h"
#include "tasks/WashControlTask.h"

Scheduler scheduler;
CarWasher* pCarWasher;

void setup() {
  scheduler.init(50);
  pCarWasher = new CarWasher();
  pCarWasher->init();

  Task* pBlinkingTask = new BlinkingTask(LED02_PIN);
  pBlinkingTask->init(2000, false);

  Task* pDetectionTask = new DetectionTask(pCarWasher);
  pDetectionTask->init(100);

  Task* pGateControlTask = new GateControlTask(pCarWasher, pBlinkingTask);
  pGateControlTask->init(100);

  Task* pWashControlTask = new WashControlTask(pCarWasher, pBlinkingTask);
  pWashControlTask->init(100);

  scheduler.addTask(pBlinkingTask);
  scheduler.addTask(pDetectionTask);
  scheduler.addTask(pGateControlTask);
  scheduler.addTask(pWashControlTask);
}

void loop() {
  scheduler.schedule();
}