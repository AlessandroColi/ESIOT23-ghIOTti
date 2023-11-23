#ifndef __TEMP_CONTROL_TASK__
#define __TEMP_CONTROL_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"

class TempControlTask: public Task {
  CarWasher* pCarWasher;
  TempSensorLM35* pTempSensor;
  long tempHighStartTime;

  enum { NORMAL, TEMP_HIGH } state;

public:
  TempControlTask(CarWasher* pCarWasher);
  void tick();
};

#endif