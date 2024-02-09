#include "WaterController.h"

WaterController::WaterController(Button* button, ServoMotor* servoMotor, Lcd* lcd) 
{
    this->button = button;
    this->servoMotor = servoMotor;
    this->lcd = lcd;
    this->init();
}

void WaterController::init() 
{
    this->servoOn();
}

bool WaterController::isButtonPressed() 
{
    button->sync();
    return button->isPressed();
}

void WaterController::writeOnLCD(String text) 
{
    lcd->clearDisplay();
    lcd->setCursor(0, 0);
    lcd->printText(text);
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

