#include "Arduino.h"
#include "config.h"

uint8_t ledPin[] = {LED01_PIN, LED02_PIN, LED03_PIN, LED04_PIN};
uint8_t pulseIntensity = 0;
uint8_t pulseDelta = 5;

extern void log(const String& msg);

void init_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(LED_CTR, OUTPUT);     
}

void reset_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], LOW);     
  }
}

void test_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], HIGH);     
    delay(500);
    digitalWrite(ledPin[i], LOW);     
  }
  for (int i = 0; i < 10; i++){
    analogWrite(LED_CTR, i*25);     
    delay(100);
  }
  for (int i = 9; i >= 0; i--){
    analogWrite(LED_CTR, i*25);     
    delay(100);
  }
}

void reset_pulsing() {
  pulseIntensity = 0;
  pulseDelta = 5;
  analogWrite(LED_CTR, pulseIntensity);   
}

void go_on_pulsing(){
  analogWrite(LED_CTR, pulseIntensity);   
  pulseIntensity = pulseIntensity + pulseDelta;
  if (pulseIntensity == 0 || pulseIntensity == 255) {
    pulseDelta = -pulseDelta ; 
  }     
  delay(15);                               
}


void turn_on_pattern(uint8_t pattern[NLEDS], long delay_time){
    for(uint8_t i = 0; i<NLEDS; i++){
        digitalWrite(ledPin[i],LOW);
        delayMicroseconds(delay_time);
    }
}

void turn_off_pattern(){
  reset_led_board();
}