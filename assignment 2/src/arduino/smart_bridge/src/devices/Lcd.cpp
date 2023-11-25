#include "Lcd.h"

Lcd::Lcd() {
    lcd.init();
    lcd.backlight();
} 

void Lcd::printText(String text) {
    lcd.print(text);
}

void Lcd::setCursor(int x, int y) {
    lcd.setCursor(x, y);
}

void Lcd::clearDisplay() {
    lcd.clear();
}

void Lcd::progressBar(int seconds){
    byte p1[8] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    };
    byte p2[8] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    };
    byte p3[8] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    };
    byte p4[8] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    };
    byte p5[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    };

    lcd.createChar(0, p1);
    lcd.createChar(1, p2);
    lcd.createChar(2, p3);
    lcd.createChar(3, p4);
    lcd.createChar(4, p5);
    
    lcd.setCursor(0,1);
    lcd.print("                ");  
    for (int i = 0; i<16; i++){
        for(int j=0; j<5; j++){
            lcd.setCursor(i, 1);
            lcd.write(j);
            delay(100*(seconds/8));
        }  
    }
}

