#include "SerialMonitorTask.h"


SerialMonitorTask:: SerialMonitorTask( CarWasher* pcw){
    this->pCarWasher = pcw; 
}

void SerialMonitorTask::init(int period){
  Task::init(period);
  Serial.begin(9600);
}

void SerialMonitorTask::tick(){
    pCarWasher->sampleTemperature();
    String msg = stateAsString() + ":" + pCarWasher->getCurrentTemperature();
    Serial.println(msg);
}

bool SerialMonitorTask::isMsgAvailable(){
    return Serial.available()>0;
}
    
String SerialMonitorTask::getMsg(){
    String msg = "";
    while (Serial.available() > 0) {
        char c = Serial.read();  //gets one byte from serial buffer
        msg += c; 
    }
    return msg ;
}

String SerialMonitorTask::stateAsString(){
    String msg;
    if(pCarWasher->isWaitingForCarState()) msg="WAITING_FOR_CAR";
    else if(pCarWasher->isCarDetectedForCheckInState()) msg="CAR_DETECTED_FOR_CHECK_IN";
    else if(pCarWasher->isEnteringWashingAreaState()) msg="ENTERING_WASHING_AREA";
    else if(pCarWasher->isReadyToWashState()) msg="READY_TO_WASH";
    else if(pCarWasher->isWashingState()) msg="WASHING";
    else if(pCarWasher->isLeavingWashingAreaState()) msg="LEAVING_WASHING_AREA";
    else if(pCarWasher->isMaintenaceState()) msg="MAINTENANCE";
    else msg="";   

    return msg;
}