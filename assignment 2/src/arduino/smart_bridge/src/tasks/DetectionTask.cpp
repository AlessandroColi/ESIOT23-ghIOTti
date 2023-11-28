#include "DetectionTask.h";

#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher) {
    this->pCarWasher = pCarWasher;
}
  
void DetectionTask::tick(){
    pCarWasher->samplePresence();
    if (pCarWasher->isWaitingForCarState() && pCarWasher->detectedPresence()) {
        pCarWasher->setCarDetectedForCheckInState();
    }
}