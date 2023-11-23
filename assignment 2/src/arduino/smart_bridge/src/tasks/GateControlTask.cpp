#include "GateControlTask.h"
#include "config.h"

GateControlTask::GateControlTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    pServoMotor = new ServoMotorImpl(MOTOR_PIN);
    pSonar = new Sonar(DIST_ECHO_PIN, DIST_TRIG_PIN, MAXTEMP);
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
        if ((pCarWasher->isEnteringWashingAreaState() && pSonar->getDistance() <= MINDIST)
                || (pCarWasher->isLeavingWashingAreaState() && pSonar->getDistance() >= MAXDIST)) {
            state = WAITING_TO_CLOSE;
            atRightDistTime = millis();
        }
        break;

    case WAITING_TO_CLOSE:
        if (pCarWasher->isEnteringWashingAreaState()) {
            if (pSonar->getDistance() > MINDIST) {
                state = OPEN;
            }
            else if (CheckTimeElapsed(N2)) {
                pCarWasher->setReadyToWashState();
                CloseGate();
            }
        }
        if (pCarWasher->isLeavingWashingAreaState()) {
            if (pSonar->getDistance() < MAXDIST) {
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