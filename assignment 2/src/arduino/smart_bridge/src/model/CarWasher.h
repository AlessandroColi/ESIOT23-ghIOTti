#ifndef __CARWASHER__
#define __CARWASHER__

#include <Arduino.h>
#include "devices/Led.h"
#include "devices/Pir.h"
#include "devices/Sonar.h"
#include "devices/ServoMotor.h"
#include "devices/Button.h"
#include "devices/TempSensorImpl.h"
#include "devices/Lcd.h"

enum State{ WAITING_FOR_CAR, CAR_DETECTED_FOR_CHECK_IN, ENTERING_WASHING_AREA, READY_TO_WASH, 
            WASHING, LEAVING_WASHING_AREA, CHECK_OUT, MAINTENANCE};

static State state = WAITING_FOR_CAR;

class CarWasher {
    
    public: 
        CarWasher();
        void init();

        void goToSleep();
        double getCurrentDistance();
        double getCurrentTemperature();
        bool detectedPresence();

        bool isWaitingForCarState();
        bool isCarDetectedForCheckInState();
        bool isEnteringWashingAreaState();
        bool isReadyToWashState();
        bool isWashingState();
        bool isLeavingWashingAreaState();
        bool isCheckOutState();
        bool isMaintenaceState();

        void setWaitingForCarState();
        void setCarDetectedForCheckInState();
        void setEnteringWashingAreaState();
        void setReadyToWashState();
        void setWashingState();
        void setLeavingWashingAreaState();
        void setCheckOutState();
        void setMaintenaceState();

        void samplePresence();
        void sampleDistance();
        void sampleTemperature();
        void printOnLcd(String text);
        void displayProgressBar(int seconds);
        void servoOn();
        void servoOff();
        void setServoPosition(int angle);
        bool isButtonClicked();

        void test();

    private:
        double distance;
        double temperature;
        bool detPresence;

        Button* pButton;
        Light* led01;
        Light* led02;
        Light* led03;
        Lcd* lcd;
        Pir* pPir;
        Sonar* pSonar;
        ServoMotor* pServoMotor;
        TempSensorLM35* pTempSensor;
};

#endif
