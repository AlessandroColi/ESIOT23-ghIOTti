#include "SerialComunication.h"
#include "config.h"

SmartRiver* SerialComunication::smartRiver;

SerialComunication::SerialComunication(SmartRiver* smartRiver) 
{
    this->smartRiver = smartRiver;
}

void SerialComunication::init() 
{
    Serial.begin(9600);
}

void SerialComunication::update() 
{

}

bool SerialComunication::isMessageAvailable() 
{
    return Serial.available() > 0;
}

String SerialComunication::getMessage() 
{
    String message = "";
    char character;

    while (isMessageAvailable() && (character = Serial.read()) != '\n') 
    {
        message += character;
    }

    return message;
}
