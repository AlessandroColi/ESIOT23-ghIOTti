#ifndef __WATER_CONTROLLER__
#define __WATER_CONTROLLER__

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "TimerOne.h"
#include "devices/ButtonImpl.h"
#include "devices/Lcd.h"
#include "devices/ServoMotorImpl.h"

class WaterController
{
    public:
        WaterController(Button *button, ServoMotor *servoMotor, Lcd *lcd);
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
};

#endif