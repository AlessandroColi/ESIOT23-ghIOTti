#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(ServoMotor* servo, Potentiometer* pot, Lcd* lcd, SmartRiver* smartRiver) 
{
    this->servo = servo;
    this->pot = pot;
    this->lcd = lcd;
    this->smartRiver = smartRiver;
}

void ValveTask::init(int period) 
{
    Task::init(period);
    valveState = AUTOMATIC;
}

void ValveTask::tick(int percentageAngle) 
{
    if (automatic) 
    {
        valveState = AUTOMATIC;
    } else
    {
        valveState = MANUAL;
    }

    switch(valveState) 
    {
        case AUTOMATIC:
            servo->setPosition(setAngle(percentageAngle));
            lcd->video(percentageAngle, "AUTOMATIC");
            lcd->clearDisplay();
            break;
        
        case MANUAL:
            int angle = map(pot->getValue(), 0, 1023, 0, 180);
            servo->setPosition(setAngle(angle));
            lcd->video(angle, "MANUAL");
            break;
    }
}

int setAngle(int percentage) 
{
    return percentage*180/100;
}