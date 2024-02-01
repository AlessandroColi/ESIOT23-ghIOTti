#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(ServoMotor* servo, Potentiometer* pot, Lcd* lcd, WaterController* waterController) 
{
    this->servo = servo;
    this->pot = pot;
    this->lcd = lcd;
    this->waterController = waterController;
}

void ValveTask::init(int period) 
{
    Task::init(period);
    valveState = AUTOMATIC;
}

void ValveTask::tick() 
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
            servo->setPosition(setAngle(valvePosition));
            lcd->video(valvePosition, "AUTOMATIC");
            lcd->clearDisplay();
            break;
        
        case MANUAL:
            int angle = map(pot->getValue(), 0, 1023, 0, 180);
            valvePosition = setAngle(angle);
            servo->setPosition(valvePosition);
            lcd->video(angle, "MANUAL");
            break;
    }
}

int setAngle(int percentage) 
{
    return percentage*180/100;
}