#ifndef __DETECTION_TASK__
#define __DETECTION_TASK__

#include "Task.h"
#include "devices/TempSensorImpl.h"
#include "model/CarWasher.h"

class DetectionTask: public Task {
  CarWasher* pCarWasher;
  long startTimer;
  enum {WAITING, DETECTED} state;

public:
  DetectionTask(CarWasher* pCarWasher);
  void tick();
};

#endif