#include "ComunicationTask.h"

ComunicationTask::ComunicationTask(WaterController* waterController) 
{
    this->waterController = waterController;
}

void ComunicationTask::init(int period) 
{
    Task::init(period);
}

void ComunicationTask::tick() 
{

    if (isMessageAvailable()) 
    {
        String msg = getMessage();
        this->waterController->setServoPosition(msg.toInt());
    }
    if(this->waterController->isAutomatic() ){
        Serial.println("AUTO");
    }else{
        Serial.println(this->waterController->getValvePosition());
    }
}

bool ComunicationTask::isMessageAvailable()
{
    return Serial.available() > 0;
}

String ComunicationTask::getMessage()
{
    String message = "";
    int percentage;
    while (Serial.available() > 0 && (percentage = Serial.read()) != '\n')  
    {
        message += char(percentage);
    }
    return message;
}