#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include <arduino.h>
#include "ServoTimer2.h"

class ServoMotorImpl : public ServoMotor 
{
    public:
        ServoMotorImpl(int pin);
        void on();
        void setPosition(int percentage);
        void off();

    private:
        int pin;
        ServoTimer2 servo;
};

#endif