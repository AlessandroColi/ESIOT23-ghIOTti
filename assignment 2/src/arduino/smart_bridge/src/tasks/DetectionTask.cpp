#include "DetectionTask.h";

#include "config.h"

DetectionTask::DetectionTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    pPir = new Pir(PIR_PIN);
}
  
void DetectionTask::tick(){
    if (pCarWasher->isWaitingForCarState() && pCarWasher->detectedPresence()) {
        pCarWasher->setCarDetectedForCheckInState();
    }
    //TODO: capire se va inserita una sleep nell'else, forse non va qui ma in CarWasher(?)
}