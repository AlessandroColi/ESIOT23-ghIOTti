#ifndef __CONFIG__
#define __CONFIG__

// leds
#define NLEDS 4

#define LED01_PIN 9
#define LED02_PIN 10
#define LED03_PIN 11
#define LED04_PIN 12

#define LED_CTR 13

//buttons and potentiometer

#define NUM_INPUT_POS NLEDS

#define BUT01_PIN 2
#define BUT02_PIN 3
#define BUT03_PIN 4
#define BUT04_PIN 5

#define POT_PIN A0

//times

#define MAX_IDLE_TIME 10000
#define TIME_IN_GAME_OVER 1000
#define T1_TIME 1000    //used for randomized time generation
#define MAX_TIME_DISPLAY 3000    //max time to display pattern
#define MIN_TIME_DISPLAY 700 
#define T3_TIME 5000    //max time to form pattern
#define T3_MIN_TIME 1000    // lower limit time to form pattern
#define INITIAL_WAIT 5000 // time given at the start to choose the difficulty

// game states
#define GAME_INTRO 1
#define GAME_WAIT_TO_START 2
#define GAME_INIT 3
#define GAME_LOOP_GENERATE_PATTERN 4
#define GAME_LOOP_DISPLAY_PATTERN 5
#define GAME_LOOP_WAITING_PLAYER_PATTERN 6
#define GAME_OVER 7
#define GAME_SLEEP 8

//difficulties

#define NO_SELECTION -1
#define DIFFICULTY_LEVELS 4

#endif