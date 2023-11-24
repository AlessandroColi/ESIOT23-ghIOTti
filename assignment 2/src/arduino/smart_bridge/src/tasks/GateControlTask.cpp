#include "GateControlTask.h"
#include "config.h"

GateControlTask::GateControlTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    state = CLOSE;
}
  
void GateControlTask::tick(){
    switch (state) {
    case CLOSE:
        if (pCarWasher->isEnteringWashingAreaState() || pCarWasher->isLeavingWashingAreaState()) {
            OpenGate();
        }        
        break;
    
    case OPEN:
        pCarWasher->sampleDistance();
        if ((pCarWasher->isEnteringWashingAreaState() && pCarWasher->getCurrentDistance() <= MINDIST)
                || (pCarWasher->isLeavingWashingAreaState() && pCarWasher->getCurrentDistance() >= MAXDIST)) {
            state = WAITING_TO_CLOSE;
            atRightDistTime = millis();
        }
        break;

    case WAITING_TO_CLOSE:
        pCarWasher->sampleDistance();
        if (pCarWasher->isEnteringWashingAreaState()) {
            if (pCarWasher->getCurrentDistance() > MINDIST) {
                state = OPEN;
            }
            else if (CheckTimeElapsed(N2)) {
                pCarWasher->setReadyToWashState();
                CloseGate();
            }
        }
        if (pCarWasher->isLeavingWashingAreaState()) {
            if (pCarWasher->getCurrentDistance() < MAXDIST) {
                state = OPEN;
            }
            else if (CheckTimeElapsed(N4)) {
                pCarWasher->setCheckOutState();
                CloseGate();
            }
        }
        break;
    }
}

bool GateControlTask::CheckTimeElapsed(long timeRequired) {
    return (millis() - atRightDistTime) >= timeRequired;
}

void GateControlTask::OpenGate() {
    pServoMotor->on();
    pServoMotor->setPosition(OPEN_POS);
    state = OPEN;
}

bool GateControlTask::CloseGate() {
    pServoMotor->setPosition(CLOSE_POS);
    pServoMotor->off();
    state = CLOSE;
}