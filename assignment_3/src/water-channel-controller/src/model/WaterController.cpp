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
    return map(pot->getValue(), 0, 1023, 0, 180);
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
    lcd->clearDisplay();
    lcd->video(value, text);
    Serial.println("-");
}

void WaterController::servoOn() 
{
    servoMotor->on();
}

void WaterController::servoOff() 
{
    servoMotor->off();
}

void WaterController::setServoPosition(int angle) 
{
    servoMotor->setPosition(angle);
}

