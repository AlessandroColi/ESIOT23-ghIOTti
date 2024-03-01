#ifndef __WATER_CONTROLLER__
#define __WATER_CONTROLLER__

#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "TimerOne.h"
#include "devices/ButtonImpl.h"
#include "devices/Lcd.h"
#include "devices/ServoMotorImpl.h"
#include <devices/Potentiometer.h>

class WaterController
{
    public:
        WaterController(Button *button, ServoMotor *servoMotor, Lcd *lcd, Potentiometer *pot);
        void init();

        long getCurrentTime();
        int getPotetiomenter();
        int getValvePosition();
        bool isAutomatic();

        void setValvePosition(int position);
        void setAutomatic(bool automatic);

        bool isButtonClicked();

        void writeOnLCD(int value, String text);

        void servoOn();
        void servoOff();
        void setServoPosition(int perc);
    
    private:
        long time;
        int valvePosition;
        bool automatic;
        
        Button* button;
        Lcd* lcd;
        ServoMotor* servoMotor;
        Potentiometer* pot;
};

#endif