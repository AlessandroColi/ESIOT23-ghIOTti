#ifndef __GATE_CONTROL_TASK__
#define __GATE_CONTROL_TASK__

#define OPEN 180
#define CLOSE 0

#include "Task.h"
#include "model/CarWasher.h"
#include "devices/ServoMotorImpl.h"

class GateControlTask: public Task {
  CarWasher* pCarWasher;
  Sonar* pSonar;
  ServoMotorImpl* pServoMotor;
  
  long enteringStateTime;
  long elapsedTime;
  enum { WAITING_ENTER, ENTERING, WAITING_EXIT, EXITING } state;

  void SetState(int state);
  long ElapsedTimeInState();
  void OpenGate(int nextState);
  void CloseGate(long timeRequired, float distanceRequired, int nextState);

public:
  GateControlTask(CarWasher* pCarWasheR);
  void tick();

};

#endif