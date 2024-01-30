#include "SmartRiver.h"
#include "config.h"
#include "devices/ButtonImpl.h"
#include "devices/Lcd.h"
#include "devices/ServoMotorImpl.h"
#include "devices/Potentiometer.h"

SmartRiver::SmartRiver() 
{
}

void SmartRiver::init() 
{
    button = new ButtonImpl(BUTTON_PIN);
    lcd = new Lcd();
    servoMotor = new ServoMotorImpl(SERVO_PIN);
    potentiometer = new Potentiometer(POT_PIN);
    servoOn();
}

bool SmartRiver::isButtonPressed() 
{
    button->sync();
    return button->isPressed();
}

void SmartRiver::writeOnLCD(String text) 
{
    lcd->clearDisplay();
    lcd->setCursor(0, 0);
    lcd->printText(text);
}

void SmartRiver::servoOn() 
{
    servoMotor->on();
}

void SmartRiver::servoOff() 
{
    servoMotor->off();
}

void SmartRiver::setServoPosition(int angle) 
{
    servoMotor->setPosition(angle);
}

