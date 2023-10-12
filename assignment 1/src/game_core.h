#ifndef __GAME_CORE__
#define __GAME_CORE__

#include "Arduino.h"

extern int game_state;

void update_game_state_time();
void change_game_state(int new_state);

/* behaviour in the specific game states */
void game_intro();
void game_wait_to_start();
void game_init();
void game_loop_generate_pattern();
void game_loop_display_pattern();
void game_loop_wait_player_pattern();
void game_over();
void game_sleep();

/* game test */
void game_test();

#endif