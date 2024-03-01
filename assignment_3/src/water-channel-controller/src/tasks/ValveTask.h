#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../devices/Potentiometer.h"
#include "../model/WaterController.h"

extern int valvePosition;

class ValveTask: public Task 
{
    public:
        ValveTask(WaterController* WaterController);
        void init(int period);
        void tick();

    private:
        WaterController* waterController;
        enum
        {
            AUTOMATIC,
            MANUAL
        } valveState;
};

#endif