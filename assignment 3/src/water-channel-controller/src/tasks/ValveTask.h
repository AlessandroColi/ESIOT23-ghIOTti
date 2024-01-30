#ifndef __VALVETASK__
#define __VALVETASK__

#include "Task.h"
#include "../devices/ServoMotorImpl.h"
#include "../devices/Potentiometer.h"
#include "../devices/Lcd.h"
#include "../model/SmartRiver.h"

class ValveTask: public Task 
{
    public:
        ValveTask(ServoMotor* servo, Potentiometer* pot, Lcd* lcd, SmartRiver* smartRiver);
        void init(int period);
        void tick(int percentageAngle);

    private:
        SmartRiver* smartRiver;
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