#ifndef __COMUNICATION_TASK__
#define __COMUNICATION_TASK__

#include "Task.h"
#include "./model/WaterController.h"

extern int valvePosition;
extern bool automatic;

class ComunicationTask: public Task 
{
    public:
        ComunicationTask(WaterController* waterController);
        void init(int period);
        void tick();

    private:
        WaterController* waterController;
        bool isMessageAvailable();
        String getMessage();
};

#endif