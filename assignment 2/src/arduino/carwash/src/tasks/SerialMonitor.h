#ifndef __SERIALMONITOR__
#define __SERIALMONITOR__

#include "Task.h"
#include "model/CarWasher.h"

class SerialMonitor: public Task {

    CarWasher* pCarWasher;

    public:
    SerialMonitor( CarWasher* pcw);
    void init(int period);
    void tick();
    bool isMsgAvailable();
    String getMsg();

    private:
    String stateAsString();
};

#endif
