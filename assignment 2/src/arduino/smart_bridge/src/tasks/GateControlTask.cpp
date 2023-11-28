#include "GateControlTask.h"
#include "config.h"

GateControlTask::GateControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask):
        pCarWasher(pCarWasher), pBlinkingTask(pBlinkingTask) {
    state = CLOSE;
}
  
void GateControlTask::tick(){
    switch (state) {
    case CLOSE:
        if (pCarWasher->isEnteringWashingAreaState()) {
            pBlinkingTask->setPeriod(BLINK_INT1);
            pBlinkingTask->setActive(true);
            OpenGate();
        }
        if (pCarWasher->isLeavingWashingAreaState()) {
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
                pBlinkingTask->setActive(false);
                pCarWasher->setReadyToWashState();
                CloseGate();
            }
        }
        if (pCarWasher->isLeavingWashingAreaState()) {
            if (pCarWasher->getCurrentDistance() < MAXDIST) {
                state = OPEN;
            }
            else if (CheckTimeElapsed(N4)) {
                CloseGate();
                pCarWasher->setCheckOutState();
            }
        }
        break;
    }
}

bool GateControlTask::CheckTimeElapsed(long timeRequired) {
    return (millis() - atRightDistTime) >= timeRequired;
}

void GateControlTask::OpenGate() {
    pCarWasher->setServoPosition(OPEN_POS);
    state = OPEN;
}

bool GateControlTask::CloseGate() {
    pCarWasher->setServoPosition(CLOSE_POS);
    state = CLOSE;
}