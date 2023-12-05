#ifndef __TASK__
#define __TASK__

#include "Arduino.h"

class Task {
    
public:
  virtual void init(int period) {
    this->period = period;
    this->active = true;
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= this->period){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  void setPeriod(int period) {
    this->period = period;
  }

  bool isActive() {
    return active;
  }

  void setActive(bool active) {
    this->active = active;
  }

protected:
  int period;
  int timeElapsed;
  bool active;
};

#endif
