#include "WashControlTask.h";

#include "config.h"

WashControlTask::WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask, SerialMonitor* pSerialMonitor): 
        pCarWasher(pCarWasher), pBlinkingTask(pBlinkingTask),pSerialMonitor(pSerialMonitor) {
    state = WAITING;
    washingTimeElapsed = 0;
}
  
void WashControlTask::tick(){
    switch(state) {
        case WAITING:
            if (pCarWasher->isReadyToWashState() && pCarWasher->isButtonClicked()) {
                washingStartTime = millis();
                pBlinkingTask->setPeriod(BLINK_INT2);
                pBlinkingTask->setActive(true);
                pCarWasher->setWashingState();
            }
            break;

        case WASHING:
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() >= MAXTEMP) {
                tempHighStartTime = millis();
                state = TEMP_HIGH;
            }
            else if ((millis() - washingStartTime + washingTimeElapsed) >= N3) {
                pBlinkingTask->setActive(false);
                state = WAITING;
                pCarWasher->setLeavingWashingAreaState();
            }
            break;
    
        case TEMP_HIGH:
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() < MAXTEMP) {
                state = WASHING;
            }
            else if ((millis() - tempHighStartTime) >= N4) {
                washingTimeElapsed = millis() - washingStartTime;
                state = MAINTENACE;
                pCarWasher->setMaintenaceState();
            }
            break;
        
        case MAINTENACE:
            if(pSerialMonitor->isMsgAvailable()){
                String msg = pSerialMonitor->getMsg();
                if(msg == "Maintenence done"){
                    washingStartTime = millis();
                    state = WASHING;
                    pCarWasher->setWashingState();
                }
            }
            break;
    }
}
