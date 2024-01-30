#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>
#include "Arduino.h"

class Lcd 
{    
    public:
        Lcd();
        void printText(String text);
        void setCursor(int x, int y);
        void clearDisplay();
        void video(int value, String text);

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif