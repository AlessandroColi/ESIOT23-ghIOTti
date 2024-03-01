#include "WaterController.h"

WaterController::WaterController(Button* button, ServoMotor* servoMotor, Lcd* lcd, Potentiometer* pot) 
{
    this->button = button;
    this->servoMotor = servoMotor;
    this->lcd = lcd;
    this->pot = pot;
    this->init();
}

void WaterController::init() 
{
    servoMotor->on();
    servoMotor->setPosition(0);
    this->automatic = true;
    this->valvePosition = 0;
}

long WaterController::getCurrentTime() 
{
    return time;
}

int WaterController::getPotetiomenter() 
{
    int val = pot->getValue();
    int perc = map(val, 0, 1023, 0, 100);

    if( val < 10){
        perc = 0;
    }else if( val > 1010){
        perc = 100;
    }

    return perc;
}

int WaterController::getValvePosition() 
{
    return valvePosition;
}

bool WaterController::isAutomatic() 
{
    return automatic;
}

void WaterController::setValvePosition(int position) 
{
    this->valvePosition = position;
}

void WaterController::setAutomatic(bool automatic) 
{
    this->automatic = automatic;
}

bool WaterController::isButtonClicked()
{
    button->sync();
    return button->isPressed();
}

void WaterController::writeOnLCD(int value, String text) 
{
    lcd->video(value, text);
}

void WaterController::servoOn() 
{
    servoMotor->on();
}

void WaterController::servoOff() 
{
    servoMotor->off();
}

void WaterController::setServoPosition(int perc) 
{
    valvePosition = perc;
    servoMotor->setPosition(map(perc,0,100,0,180));
}

