#ifndef __SERIALMONITOR__
#define __SERIALMONITOR__

#include "model/CarWasher.h"

class SerialMonitor{

    CarWasher* pCarWasher;

    public:
    SerialMonitor( CarWasher* pcw);
    void init();
    void update();
    bool isMsgAvailable();
    String getMsg();

    private:
    String stateAsString();
};

#endif
