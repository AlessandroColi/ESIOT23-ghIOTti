#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "Task.h"
#include "devices/Led.h"

class BlinkingTask: public Task {
  int pin;
  Light* led;
  enum {ON, OFF} state;

public:
  BlinkingTask(int pin);
  void init(int period);
  void tick();
};

#endif