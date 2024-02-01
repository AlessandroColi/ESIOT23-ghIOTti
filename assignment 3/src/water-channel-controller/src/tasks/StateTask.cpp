#include "StateTask.h"

StateTask::StateTask(WaterController* waterController) 
{
    this->waterController = waterController;
    automatic = true;
}

void StateTask::tick() 
{
    if (this->waterController->isButtonPressed()) 
    {
        if (automatic)
        {
            this->waterController->writeOnLCD("Manual");
            automatic = false;
        } else 
        {
            this->waterController->writeOnLCD("Automatic");
            automatic = true;
        }
    }
}