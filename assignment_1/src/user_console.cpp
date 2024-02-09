#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "game_core.h"

#include <EnableInterrupt.h>

#define BOUNCING_TIME 100

uint8_t inputPins[] = {BUT01_PIN, BUT02_PIN, BUT03_PIN, BUT04_PIN};

bool wasAlreadyPressed[] = {false, false, false, false };

long lastButtonPressedTimeStamps[NUM_INPUT_POS];

void button_handler(int i);

void button_handler_0() { button_handler(0); }
void button_handler_1() { button_handler(1); }
void button_handler_2() { button_handler(2); }
void button_handler_3() { button_handler(3); }

uint8_t inputPattern[NUM_INPUT_POS];
int recived = 0;

void (*button_handlers[4])() = {button_handler_0, button_handler_1, button_handler_2, button_handler_3};

void button_handler(int i) {
  long ts = millis();
  if (ts - lastButtonPressedTimeStamps[i] > BOUNCING_TIME) {
    lastButtonPressedTimeStamps[i] = ts;
    int status = digitalRead(inputPins[i]);
    if (status == HIGH && !wasAlreadyPressed[i]) {
      wasAlreadyPressed[i] = true;
      if (getState() == GAME_LOOP_WAITING_PLAYER_PATTERN) {
        turn_on_led(i);
        inputPattern[recived] = i;
        recived++;
      }
    }
  }
}

int read_difficulty_level() {
  int read = analogRead(POT_PIN);
  int width = 1023 / NLEDS;
  for (int i = 1; i < NLEDS; i++) {
    if(read < width*i) {
      return i;
    }
  }
  return NLEDS;
}

uint8_t *get_current_input_pattern() {
  return inputPattern;
}

void init_player_console() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    pinMode(inputPins[i], INPUT);  
    enableInterrupt(inputPins[i], button_handlers[i], CHANGE);       
  }
}

void print_on_console(const String& msg) {
  Serial.println(msg);
}

void reset_player_input() {
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    inputPattern[i] = NUM_INPUT_POS;      
    lastButtonPressedTimeStamps[i] = ts;    
    wasAlreadyPressed[i] = false;
  }
  recived = 0;
  delay(BOUNCING_TIME);
}

bool b1_pressed() {
  return wasAlreadyPressed[0];
}

void  test_player_input() {
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    if (inputPattern[i]) {
      Serial.println(String("button ") + i + " pressed"); 
    }
  }
  int value = analogRead(POT_PIN);
  Serial.println(value);
}