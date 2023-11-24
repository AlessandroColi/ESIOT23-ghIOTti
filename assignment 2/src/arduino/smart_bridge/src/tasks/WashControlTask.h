#ifndef __WASH_CONTROL_TASK__
#define __WASH_CONTROL_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"
#include "devices/ButtonImpl.h"
#include "BlinkingTask.h"

class WashControlTask: public Task {
  CarWasher* pCarWasher;
  BlinkingTask* pBlinkingTask;
  ButtonImpl* pButton;
  long washingStartTime;
  long washingTimeElapsed;
  long tempHighStartTime;

  void StopWashing();
  void StartWashing();
  enum { WAITING, WASHING, TEMP_HIGH, MAINTENACE } state;

public:
  WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask);
  void tick();
};

#endif