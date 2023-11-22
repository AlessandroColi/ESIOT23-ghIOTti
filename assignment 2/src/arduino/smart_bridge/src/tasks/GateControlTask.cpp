#include "GateControlTask.h"
#include "config.h"

GateControlTask::GateControlTask(CarWasher* pCarWasher): pCarWasher(pCarWasher) {
    pServoMotor = new ServoMotorImpl(MOTOR_PIN);
    pSonar = new Sonar(DIST_ECHO_PIN, DIST_TRIG_PIN, MAXTEMP);
    SetState(WAITING_ENTER);
}
  
void GateControlTask::tick(){
    switch (state)
    {
    case WAITING_ENTER:
        if (pCarWasher->isCarDetectedForCheckInState()) {
            OpenGate(ENTERING);
        }
        break;
    
    case ENTERING:
        CloseGate(N2, MINDIST, WAITING_EXIT);
        break;
    
    case WAITING_EXIT:
        if (pCarWasher->isLeavingWashingAreaState()) {
            OpenGate(EXITING);
        }
        break;

    case EXITING:
        CloseGate(N4, MAXDIST, WAITING_ENTER);
        break;
    }
}

void GateControlTask::SetState(int s) {
    state = s;
    enteringStateTime = millis();
}

long GateControlTask::ElapsedTimeInState() {
    return millis() - enteringStateTime;
}

void GateControlTask::OpenGate(int nextState) {
    pServoMotor->on();
    pServoMotor->setPosition(OPEN);
    SetState(nextState);
}

void GateControlTask::CloseGate(long timeRequired, float distanceRequired, int nextState) {
    if (pSonar->getDistance() <= distanceRequired) {
        if (elapsedTime >= timeRequired) {
            pServoMotor->setPosition(CLOSE);
            pServoMotor->off();
            SetState(nextState);
        }
    }
    else {
        elapsedTime = 0;
    }
}