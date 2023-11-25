#include "WashControlTask.h";

#include "config.h"

WashControlTask::WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask): 
        pCarWasher(pCarWasher), pBlinkingTask(pBlinkingTask) {
    state = WAITING;
}
  
void WashControlTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isReadyToWashState() && pCarWasher->isButtonClicked()) {
                StartWashing();
                washingTimeElapsed = 0;
                pCarWasher->setWashingState();
                pBlinkingTask->setPeriod(BLINK_INT2);
                pBlinkingTask->setActive(true);
            }
            break;
        case WASHING:
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() >= MAXTEMP) {
                state = TEMP_HIGH;
                tempHighStartTime = millis();
                StopWashing();
            }
            if (washingTimeElapsed >= N3) {
                state = WAITING;
                pCarWasher->setLeavingWashingAreaState();
                pBlinkingTask->setActive(false);
            }
            break;
    
        case TEMP_HIGH:
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() < MAXTEMP) {
                StartWashing();
            }
            else if ((millis() - tempHighStartTime) >= N4) {
                state = MAINTENACE;
                pCarWasher->setMaintenaceState();
                StopWashing();
            }
            break;
        
        case MAINTENACE:
            //TO-DO: aggiungere che se si clicca il bottone torna nello stato normale di lavaggio (mi manca sapere come sarebbe l'implementazione di java).
            break;
    }
}

void WashControlTask::StopWashing() {
    washingTimeElapsed += (washingStartTime - millis());
}

void WashControlTask::StartWashing() {
    state = WASHING;
    washingStartTime = millis();
}