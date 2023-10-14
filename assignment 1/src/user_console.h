/*********
 * 
 * USER CONSOLE
 * 
 * This module implements the user console,
 * containing the buttons for interacting
 * with the user as well as the console
 * to output the messages.
 * 
 */
#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__
#include "Arduino.h" 

void init_player_console();

void button_handler( int i);

void print_on_console(const String &msg);

/* read the difficulty level */
int read_difficulty_level();

/* check if the player started the game */
bool player_input_started();

/* reset the input, at each interation */
void reset_player_input();

/* get current pattern inserted by player, returns the reference to an arry of NLEDS elements */
uint8_t * get_current_input_pattern();

/* for testing */
void test_player_input();

/* for debugging */
void log(const String& msg);
 


#endif