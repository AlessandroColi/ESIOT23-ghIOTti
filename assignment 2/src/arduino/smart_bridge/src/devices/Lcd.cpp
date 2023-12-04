#include "Lcd.h"

Lcd::Lcd() {
    lcd.init();
    lcd.backlight();

      /* LCD Progress Bar Characters, create your custom bars */
    byte bar1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
    byte bar2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
    byte bar3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
    byte bar4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
    byte bar5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
    
    lcd.createChar(1, bar1);
    lcd.createChar(2, bar2);
    lcd.createChar(3, bar3);
    lcd.createChar(4, bar4);
    lcd.createChar(5, bar5);
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

void Lcd::progressBar(int perc){
  int full = perc/5;
  int limit = perc % 5;

  for(int row = 1 ; row < 4 ; row++){
    for (int x = 0; x < full; x++)                        // Print all the filled blocks
    {
      lcd.setCursor (x, row);
      lcd.write(byte(5));
      delay(10);                                         //allow to write prev block
    }
    lcd.setCursor (full, row);
    if (limit != 0)lcd.write(byte(limit));
  }
}