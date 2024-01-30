#include "StateTask.h"

StateTask::StateTask(SmartRiver* smartRiver) 
{
    this->smartRiver = smartRiver;
    automatic = true;
}

void StateTask::tick() 
{
    if (this->smartRiver->isButtonPressed()) 
    {
        if (automatic)
        {
            this->smartRiver->writeOnLCD("Manual");
            automatic = false;
        } else 
        {
            this->smartRiver->writeOnLCD("Automatic");
            automatic = true;
        }
    }
}