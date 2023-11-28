#ifndef __SERIALMONITOR__
#define __SERIALMONITOR__

#include "model/CarWasher.h"

class SerialMonitor{

    CarWasher* pCarWasher;

    SerialMonitor( CarWasher* pcw);

    public:
    void init();
    void update();
    bool isMsgAvailable();
    String getMsg();

    private:
    String stateAsString();
};

#endif
