#include "WashControlTask.h";

#include "config.h"

WashControlTask::WashControlTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    pTempSensor = new TempSensorLM35(TEMP_PIN);
    pButton = new ButtonImpl(START_BTN);
    state = WAITING;
}
  
void WashControlTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isReadyToWashState() && pButton->isClicked()) {
                StartWashing();
                washingTimeElapsed = 0;
                pCarWasher->setWashingState();
            }
            break;
        case WASHING:
            if (pTempSensor->getTemperature() >= MAXTEMP) {
                state = TEMP_HIGH;
                tempHighStartTime = millis();
                StopWashing();
            }
            if (washingTimeElapsed >= N3) {
                state = WAITING;
                pCarWasher->setLeavingWashingAreaState();
            }
            break;
    
        case TEMP_HIGH:
            if (pTempSensor->getTemperature() < MAXTEMP) {
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