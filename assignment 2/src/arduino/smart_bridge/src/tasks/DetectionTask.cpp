#include "DetectionTask.h"

#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher) {
    this->pCarWasher = pCarWasher;
    startTimer = millis();
}
  
void DetectionTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isWaitingForCarState() && pCarWasher->detectedPresence()) {
                state = DETECTED;
                startTimer = millis();
            }
            break;

        case DETECTED:
            if (millis() - startTimer >= N1) {
                state = WAITING;
                pCarWasher->setEnteringWashingAreaState();
            }
            break;
    }
}