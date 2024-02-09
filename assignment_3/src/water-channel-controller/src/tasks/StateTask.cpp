#include "StateTask.h"

StateTask::StateTask(WaterController* waterController) 
{
    this->waterController = waterController;
}

void StateTask::init(int period)
{
    Task::init(period);
}

void StateTask::tick() 
{
    if (this->waterController->isButtonPressed()) 
    {
        if (this->waterController->isAutomatic())
        {
            this->waterController->setAutomatic(false);
        } else 
        {
            this->waterController->setAutomatic(true);
        }
    }
}