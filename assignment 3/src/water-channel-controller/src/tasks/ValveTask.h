#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../devices/Potentiometer.h"
#include "../model/WaterController.h"

extern int valvePosition;

class ValveTask: public Task 
{
    public:
        ValveTask(ServoMotor* servo, Potentiometer* pot, Lcd* lcd, WaterController* WaterController);
        void init(int period);
        void tick();

    private:
        WaterController* waterController;
        ServoMotor* servo;
        Potentiometer* pot;
        Lcd* lcd;
        enum
        {
            AUTOMATIC,
            MANUAL
        } valveState;
        int setAngle(int percentage);
};

#endif