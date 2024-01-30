#ifndef __SMART_RIVER__
#define __SMART_RIVER__

#include <Arduino.h>
#include <devices/Button.h>
#include <devices/LCD.h>
#include <devices/ServoMotor.h>
#include <devices/Potentiometer.h>

class SmartRiver
{
    public:
        SmartRiver();
        void init();
        bool isButtonPressed();
        void writeOnLCD(String text);
        void servoOn();
        void servoOff();
        void setServoPosition(int angle);
    
    private:
        double distance;
        long time;
        
        Button* button;
        Lcd* lcd;
        ServoMotor* servoMotor;
        Potentiometer* potentiometer;
};

#endif