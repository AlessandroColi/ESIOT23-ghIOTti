#include "SerialMonitor.h"


SerialMonitor:: SerialMonitor( CarWasher* pcw){
    this->pCarWasher = pcw; 
}

void SerialMonitor::init(){
  Serial.begin(9600);
}

void SerialMonitor:: update(){
    pCarWasher->sampleTemperature();
    String msg = stateAsString() + ":" + pCarWasher->getCurrentTemperature();
    Serial.println(msg);
}

bool SerialMonitor:: isMsgAvailable(){
    return Serial.available()>0;
}
    
String SerialMonitor:: getMsg(){
    String msg = "";
    while (Serial.available() > 0) {
        char c = Serial.read();  //gets one byte from serial buffer
        msg += c; 
        delay(3);  //delay to allow buffer to fill 
    }
    return msg ;
}

String SerialMonitor:: stateAsString(){
    String msg;
    switch(pCarWasher->state){
        case CarWasher:: WAITING_FOR_CAR:
            msg = "WAITING_FOR_CAR";
            break;
        case CarWasher:: CAR_DETECTED_FOR_CHECK_IN:
            msg = "CAR_DETECTED_FOR_CHECK_IN";
            break;
        case CarWasher:: ENTERING_WASHING_AREA:
            msg = "ENTERING_WASHING_AREA";
            break;
        case CarWasher:: READY_TO_WASH:
            msg = "READY_TO_WASH";
            break;
        case CarWasher:: WASHING:
            msg = "WASHING";
            break;
        case CarWasher:: LEAVING_WASHING_AREA:
            msg = "LEAVING_WASHING_AREA";
            break;
        case CarWasher:: CHECK_OUT:
            msg = "CHECK_OUT";
            break;
        case CarWasher:: MAINTENANCE:
            msg = "MAINTENANCE";
            break;   
        default:
            msg="";   
    }
    return msg;
}