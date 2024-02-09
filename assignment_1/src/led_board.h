/*********
 * 
 * LED BOARD
 * 
 * This module implements the Led Board,
 * containing the 4 leds.
 * 
 */
#ifndef __LED_BOARD__
#define __LED_BOARD__

#include "Arduino.h"

void init_led_board();
void reset_led_board();

void turn_on_pattern(uint8_t pattern[NLEDS], long delay_time);
void turn_off_pattern();

void reset_pulsing();
void go_on_pulsing();
void turn_on_leds();
void turn_on_led(int i);

/* for testing */
void test_led_board();

#endif