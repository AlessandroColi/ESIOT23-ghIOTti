#ifndef __WASH_CONTROL_TASK__
#define __WASH_CONTROL_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"
#include "BlinkingTask.h"
#include "SerialMonitor.h";


class WashControlTask: public Task {
  CarWasher* pCarWasher;
  BlinkingTask* pBlinkingTask;
  SerialMonitor* pSerialMonitor;
  long washingStartTime;
  long washingTimeElapsed;
  long tempHighStartTime;

  enum { WAITING, WASHING, TEMP_HIGH, MAINTENACE } internal_state;

public:
  WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask, SerialMonitor* pSerialMonitor);
  void tick();
};

#endif