#include "GateControlTask.h"
#include "config.h"

GateControlTask::GateControlTask(CarWasher* pCarWasher, BlinkingTask* pBlinkingTask):
        pCarWasher(pCarWasher), pBlinkingTask(pBlinkingTask) {
    internal_state = CLOSE;
}
  
void GateControlTask::tick(){
    switch (internal_state) {
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
            internal_state = WAITING_TO_CLOSE;
            atRightDistTime = millis();
        }
        break;

    case WAITING_TO_CLOSE:
        pCarWasher->sampleDistance();
        if (pCarWasher->isEnteringWashingAreaState()) {
            if (pCarWasher->getCurrentDistance() > MINDIST) {
                internal_state = OPEN;
            }
            else if (CheckTimeElapsed(N2)) {
                pBlinkingTask->setActive(false);
                pCarWasher->setReadyToWashState();
                CloseGate();
            }
        }
        if (pCarWasher->isLeavingWashingAreaState()) {
            if (pCarWasher->getCurrentDistance() < MAXDIST) {
                internal_state = OPEN;
            }
            else if (CheckTimeElapsed(N4)) {
                CloseGate();
                pCarWasher->setWaitingForCarState();
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
    internal_state = OPEN;
}

bool GateControlTask::CloseGate() {
    pCarWasher->setServoPosition(CLOSE_POS);
    internal_state = CLOSE;
}