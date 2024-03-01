#include "Lcd.h"

Lcd::Lcd() 
{
    lcd.init();
    lcd.backlight();
}

void Lcd::printText(String text) 
{
    lcd.print(text);
}

void Lcd::setCursor(int x, int y) 
{
    lcd.setCursor(x, y);
}

void Lcd::clearDisplay() 
{
    lcd.clear();
}

void Lcd::video(int value, String text) 
{
    this->clearDisplay();
    char buffer[20]; // 20 is the max length of the string
    sprintf(buffer, "valve: %d%%\%", value);

    lcd.setCursor(0, 0);
    lcd.print(buffer);

    lcd.setCursor(0, 1);
    lcd.print("mode: " + text);
}