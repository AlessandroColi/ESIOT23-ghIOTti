#include "TempControlTask.h";

#include "config.h"

TempControlTask::TempControlTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    pTempSensor = new TempSensorLM35(TEMP_PIN);
    state = NORMAL;
}
  
void TempControlTask::tick(){
    switch(state) {
        case NORMAL:
            if (pCarWasher->isWashingState() && pTempSensor->getTemperature() >= MAXTEMP) {
                state = TEMP_HIGH;
                tempHighStartTime = millis();
            }
            break;
    
        case TEMP_HIGH:
            if (pTempSensor->getTemperature() < MAXTEMP) {
                state = NORMAL;
            }
            else if ((millis() - tempHighStartTime) >= N4) {
                pCarWasher->setMaintenaceState();
            }
            if (pCarWasher->isMaintenaceState()) {
                //TO-DO: aggiungere che se si clicca il bottona torna nello stato normale di lavaggio.
                // mi manca sapere come sarebbe l'implementazione di java.
            }
            break;
    }
}
