#ifndef __WASH_CONTROL_TASK__
#define __WASH_CONTROL_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"
#include "devices/ButtonImpl.h"

class WashControlTask: public Task {
  CarWasher* pCarWasher;
  TempSensorLM35* pTempSensor;
  ButtonImpl* pButton;
  long washingStartTime;
  long washingTimeElapsed;
  long tempHighStartTime;

  void StopWashing();
  void StartWashing();
  enum { WAITING, WASHING, TEMP_HIGH, MAINTENACE } state;

public:
  WashControlTask(CarWasher* pCarWasher);
  void tick();
};

#endif