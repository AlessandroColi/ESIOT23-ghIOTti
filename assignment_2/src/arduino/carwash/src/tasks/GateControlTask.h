#ifndef __GATE_CONTROL_TASK__
#define __GATE_CONTROL_TASK__

#define OPEN_POS 100
#define CLOSE_POS 0

#include "Task.h"
#include "model/CarWasher.h"
#include "BlinkingTask.h"

class GateControlTask: public Task {
  CarWasher* pCarWasher;
  BlinkingTask* pBlinkingTask;
  
  unsigned long atRightDistTime;
  enum { OPEN, CLOSE, WAITING_TO_CLOSE } internal_state;

  bool CheckTimeElapsed(unsigned long timeRequired);
  void OpenGate();
  void CloseGate();

public:
  GateControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask);
  void tick();

};

#endif