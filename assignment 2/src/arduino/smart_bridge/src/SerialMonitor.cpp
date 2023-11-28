#include "SerialMonitor.h"

CarWasher* pCarWasher;


SerialMonitor:: SerialMonitor( CarWasher* pcw){
    this->pCarWasher = pcw; 
}

void init(){
  Serial.begin(9600);
}

void update(){
    pCarWasher->sampleTemperature();
    String msg = stateAsString(pCarWasher.getState()) + ":" + pCarWasher.getCurrentTemperature();
    Serial.println(msg);
}

bool isMsgAvailable(){
    return Serial.available()>0;
}
    
String getMsg(){
    String msg = "";
    while (Serial.available() > 0) {
        char c = Serial.read();  //gets one byte from serial buffer
        msg += c; 
        delay(3);  //delay to allow buffer to fill 
    }
    return msg ;
}

String stateAsString(state state){
    String msg;
    switch(state){
        case WAITING_FOR_CAR:
            msg = "WAITING_FOR_CAR";
            break;
        case CAR_DETECTED_FOR_CHECK_IN:
            msg = "CAR_DETECTED_FOR_CHECK_IN";
            break;
        case ENTERING_WASHING_AREA:
            msg = "ENTERING_WASHING_AREA";
            break;
        case READY_TO_WASH:
            msg = "READY_TO_WASH";
            break;
        case WASHING:
            msg = "WASHING";
            break;
        case LEAVING_WASHING_AREA:
            msg = "LEAVING_WASHING_AREA";
            break;
        case CHECK_OUT:
            msg = "CHECK_OUT";
            break;
        case MAINTENANCE:
            msg = "MAINTENANCE";
            break;   
        default:
            msg="";   
    }
    return msg;
}