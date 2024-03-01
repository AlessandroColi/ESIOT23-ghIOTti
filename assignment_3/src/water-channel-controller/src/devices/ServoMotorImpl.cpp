#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin) 
{
    this->pin = pin;
}

void ServoMotorImpl::on() 
{
    // updated values: min is 544, max 2400 (see ServoTimer2 doc)
    servo.attach(pin); //, 544, 2400);
}

void ServoMotorImpl::setPosition(int angle) 
{
    // 750 -> 0, 2250 --> 180
    //750 + angle*(2250-750)/180
    // updated values: min is 544, max 2400 (see ServoTimer2 doc)
    float coeff = (2400-544)/180.0;
    servo.write(544 + angle*coeff);
}

void ServoMotorImpl::off() 
{
    servo.detach();
}