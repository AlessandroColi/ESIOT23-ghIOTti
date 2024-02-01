#ifndef __STATETASK__
#define __STATETASK__

#include "Task.h"
#include "../devices/ButtonImpl.h"
#include "../model/WaterController.h"

bool automatic;

class StateTask: public Task
{
    public:
        StateTask(WaterController* WaterController);
        void tick();

    private:
        WaterController* waterController;
};

#endif