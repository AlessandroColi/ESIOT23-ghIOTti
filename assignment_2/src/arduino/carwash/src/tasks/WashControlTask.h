#ifndef __WASH_CONTROL_TASK__
#define __WASH_CONTROL_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"
#include "BlinkingTask.h"
#include "SerialMonitorTask.h"


class WashControlTask: public Task {
  CarWasher* pCarWasher;
  BlinkingTask* pBlinkingTask;
  SerialMonitorTask* pSerialMonitor;
  long washingStartTime;
  long washingTimeElapsed;
  long tempHighStartTime;

  enum { WAITING, WASHING, TEMP_HIGH, MAINTENACE } internal_state;

public:
  WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask, SerialMonitorTask* pSerialMonitor);
  void tick();
};

#endif