#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../devices/ButtonImpl.h"
#include "../model/WaterController.h"

extern bool automatic;

class StateTask: public Task
{
    public:
        void tick();
        void init(int period);
        StateTask(WaterController* WaterController);

    private:
        WaterController* waterController;
};

#endif