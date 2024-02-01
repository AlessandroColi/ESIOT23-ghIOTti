#include "CominicationTask.h"

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

    StaticJsonDocument<200> doc;

    doc["valvePosition"] = valvePosition;

    serializeJson(doc, Serial);
    Serial.println("");
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