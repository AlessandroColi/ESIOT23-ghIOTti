#include "Arduino.h"
#include "config.h"

#include <EnableInterrupt.h>

#define BOUNCING_TIME 100

uint8_t inputPins[] = {BUT01_PIN, BUT02_PIN, BUT03_PIN, BUT04_PIN};

bool wasAlreadyPressed[] = {false, false, false, false };

long lastButtonPressedTimeStamps[NUM_INPUT_POS];

void button_handler(int i);
void button_handler_0(){ button_handler(0); }
void button_handler_1(){ button_handler(1); }
void button_handler_2(){ button_handler(2); }
void button_handler_3(){ button_handler(3); }

uint8_t inputPattern[NUM_INPUT_POS];
int recived = 0;

void (*button_handlers[4])() = { button_handler_0, button_handler_1, button_handler_2, button_handler_3 };

void button_handler(int i){
  long ts = millis();
  if (ts - lastButtonPressedTimeStamps[i] > BOUNCING_TIME && !wasAlreadyPressed[i]){
    lastButtonPressedTimeStamps[i] = ts;
    int status = digitalRead(inputPins[i]);
    if (status == HIGH) { 
        wasAlreadyPressed[i] = true;
        inputPattern[recived] = i;
        recived++;
    }
  }
}

int read_difficulty_level(){
  return map(analogRead(POT_PIN), 0, 1023, 1, DIFFICULTY_LEVELS);
}

uint8_t* get_current_input_pattern(){
  return inputPattern;
}

void init_player_console(){
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    pinMode(inputPins[i], INPUT);  
    enableInterrupt(inputPins[i], button_handlers[i], CHANGE);       
  }
}

void print_on_console(const String& msg){
  Serial.println(msg);
}

void reset_player_input(){
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    inputPattern[i] = NUM_INPUT_POS;      
    lastButtonPressedTimeStamps[i] = ts;    
    wasAlreadyPressed[i] = false;
  }
  recived=0;
  delay(BOUNCING_TIME);
  log("input reset");
}

bool player_input_started(){
  if (inputPattern[0]<NUM_INPUT_POS){
    return true;
  } else {
    return false;
  }
}

void log(const String& msg){
  #ifdef __DEBUG__
  Serial.println(msg);
  #endif
}


void test_player_input(){
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    if (inputPattern[i]) {
      Serial.println(String("button ") + i + " pressed"); 
    }
  }
  int value = analogRead(POT_PIN);
  Serial.println(value);
}