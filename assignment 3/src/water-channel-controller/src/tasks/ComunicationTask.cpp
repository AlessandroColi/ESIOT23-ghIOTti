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
        valvePosition = getMessage().toInt();
    }

    Serial.print("{");
    Serial.print("\"valvePosition\":");
    Serial.print(valvePosition);
    Serial.println("}");
}

bool ComunicationTask::isMessageAvailable()
{
    return Serial.available() > 0;
}

String ComunicationTask::getMessage()
{
    String message = "";
    char character;
    while (Serial.available() > 0 && (character = Serial.read()) != '\n')  
    {
        message += character;
    }
    return message;
}