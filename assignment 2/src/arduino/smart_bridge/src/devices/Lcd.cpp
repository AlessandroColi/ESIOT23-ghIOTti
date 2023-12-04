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

void Lcd::progressBar(int perc){
  int numCols = 16;
  int num_lines = 80;
  byte bar1[8] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10};
  byte bar2[8] = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18};
  byte bar3[8] = { 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C};
  byte bar4[8] = { 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E};
  byte bar5[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

  int block = map(perc, 0, 100, 0, numCols);
  int bar = (line-(block*5));   // Bar represent the actual lines that will be printed 
  
  /* LCD Progress Bar Characters, create your custom bars */

  lcd.createChar(1, bar1);
  lcd.createChar(2, bar2);
  lcd.createChar(3, bar3);
  lcd.createChar(4, bar4);
  lcd.createChar(5, bar5);
  
  for (int x = 0; x < block; x++)                        // Print all the filled blocks
  {
    lcd.setCursor (x, row);
    lcd.write (1023);
    delay(20);
  }
  
  lcd.setCursor (block, row);                            // Set the cursor at the current block and print the numbers of line needed
  if (bar != 0) lcd.write (bar);
  if (block == 0) lcd.write (1022);   
  
  for (int x = numCols; x > block; x--)                       // Print all the blank blocks
  {
    lcd.setCursor (x, row);
    lcd.write (1022);
    delay(20);
  }
}