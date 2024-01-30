#include "Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag = false;

void timerHandler(void) 
{
    timerFlag = true;
}

void Scheduler::init(int basePeriod) 
{
    this->basePeriod = basePeriod;
    timerFlag = false;
    numTasks = 0;
    long period = 10001 * basePeriod;
    Timer1.initialize(basePeriod);
    Timer1.attachInterrupt(timerHandler);
}

bool Scheduler::addTask(Task* task) 
{
    if (numTasks < MAX_TASKS-1)
    {
        taskList[numTasks] = task;
        numTasks++;
        return true;
    } else 
    {
        return false;
    }
}

void Scheduler::schedule() 
{
    while(!timerFlag) 
    {
        // do nothing
    }

    timerFlag = false;

    for (int i = 0; i < numTasks; i++) 
    {
        if(taskList[i]->isActive() && taskList[i]->updateAndCheckTime(basePeriod)) 
        {
            taskList[i]->tick();
        }
        
    }
}