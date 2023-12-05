#ifndef __SERIALMONITOR__
#define __SERIALMONITOR__

#include "Task.h"
#include "model/CarWasher.h"

class SerialMonitorTask: public Task {

    CarWasher* pCarWasher;

    public:
    SerialMonitorTask( CarWasher* pcw);
    void init(int period);
    void tick();
    bool isMsgAvailable();
    String getMsg();

    private:
    String stateAsString();
};

#endif
