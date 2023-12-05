#include "WashControlTask.h"

#include "config.h"

WashControlTask::WashControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask, SerialMonitor* pSerialMonitor): 
        pCarWasher(pCarWasher), pBlinkingTask(pBlinkingTask),pSerialMonitor(pSerialMonitor) {
    internal_state = WAITING;
    washingTimeElapsed = 0;
}
  
void WashControlTask::tick(){
    switch(internal_state) {
        case WAITING:
            if (pCarWasher->isReadyToWashState() && pCarWasher->isButtonClicked()) {
                washingStartTime = millis();
                pBlinkingTask->setPeriod(BLINK_INT2);
                pBlinkingTask->setActive(true);
                pCarWasher->setWashingState();
                washingTimeElapsed = 0;
                internal_state=WASHING;
            }
            break;

        case WASHING:
            pCarWasher->showProgress(100*(millis() - washingStartTime + washingTimeElapsed)/N3);
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() >= MAXTEMP) {
                tempHighStartTime = millis();
                internal_state = TEMP_HIGH;
            }
            else if ((millis() - washingStartTime + washingTimeElapsed) >= N3) {
                pBlinkingTask->setActive(false);
                internal_state = WAITING;
                pCarWasher->setLeavingWashingAreaState();
            }
            break;
    
        case TEMP_HIGH:
            pCarWasher->showProgress(100*(millis() - washingStartTime + washingTimeElapsed)/N3);
            pCarWasher->sampleTemperature();
            if (pCarWasher->getCurrentTemperature() < MAXTEMP) {
                internal_state = WASHING;
            }
            else if ((millis() - tempHighStartTime) >= N4) {
                washingTimeElapsed = millis() - washingStartTime;
                internal_state = MAINTENACE;
                pCarWasher->setMaintenaceState();
            }
            break;
        
        case MAINTENACE:
            if(pSerialMonitor->isMsgAvailable() || pCarWasher->isButtonClicked()){
                String msg = pSerialMonitor->getMsg();
                if(msg == "Maintenence done" || true){
                    washingStartTime = millis();
                    internal_state = WASHING;
                    pCarWasher->setWashingState();
                }
            }
            break;
    }
}
