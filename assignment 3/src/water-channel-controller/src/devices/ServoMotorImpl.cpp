#include "ServoMotorImpl.h"
#include "Arduino.h"

ServoMotorImpl::ServoMotorImpl(int pin) {
    this->pin = pin;
}

void ServoMotorImpl::on() {
    // updated values: min is 544, max 2400 (see ServoTimer2 doc)
    motor.attach(pin); //, 544, 2400);
}

void ServoMotorImpl::setPosition(int percentage) {
    double angle = percentage * 1.8;
    // 750 -> 0, 2250 --> 180
    //750 + angle*(2250-750)/180
    // updated values: min is 544, max 2400 (see ServoTimer2 doc)
    float coeff = (2400-544)/180.0;
    motor.write(544 + angle*coeff);
}

void ServoMotorImpl::off() {
    motor.detach();
}