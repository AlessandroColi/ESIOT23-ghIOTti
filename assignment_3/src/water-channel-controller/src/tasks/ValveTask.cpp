#include "ValveTask.h"
#include "StateTask.h"

ValveTask::ValveTask(WaterController* waterController) 
{
    this->waterController = waterController;
}

void ValveTask::init(int period) 
{
    Task::init(period);
    valveState = AUTOMATIC;
}

void ValveTask::tick() 
{
    if (waterController->isAutomatic()) 
    {
        valveState = AUTOMATIC;
    } else
    {
        valveState = MANUAL;
    }

    switch(valveState) 
    {
        int valvePosition;
        case AUTOMATIC:
            valvePosition = waterController->getValvePosition();
            waterController->setServoPosition(valvePosition);
            waterController->writeOnLCD(valvePosition, "AUTOMATIC");
            break;
        
        case MANUAL:
            valvePosition = waterController->getPotetiomenter();
            waterController->setServoPosition(valvePosition);
            waterController->writeOnLCD(valvePosition, "MANUAL");
            break;
    }
}