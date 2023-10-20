#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

/* current pattern to be generated */
uint8_t current_pattern[NLEDS];

/* has the pattern already been generated for this GAME_LOOP_GENERATE_PATTERN state */
bool pattern_generated;

/* current max time to generate the pattern (random) */
long max_time_to_generate_pattern;

/* current max time that can be used to input the pattern */
long max_time_to_form_pattern;

/* difficulty level */
int difficulty_level;

/* difficulty scaling factor */
double difficulty_scaling_factor = 1;

/* the score */
long score = 0;

/* current game state */
int game_state;

/* time in which the game entered in the game state */
long entered_state_time;

/* how long it the game is in current state */
long current_time_in_state;

/* time between turn off*/
long time_to_display_pattern;

/* =========== procedures about game state ======== */

void change_game_state(int new_state)
{
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time(){
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level()
{
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level)
  {
    difficulty_level = new_difficulty_level;
    print_on_console(String("New difficulty Level: ") + difficulty_level);
  }
}

void game_intro(){
  reset_player_input();
  reset_led_board();
  print_on_console("Welcome to the Catch the Led Pattern Game. Press Key B1 to Start");
  reset_pulsing();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start(){
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    if (b1_pressed()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void initPattern(){
  max_time_to_generate_pattern = T1_TIME + random(T1_TIME*3);
  pattern_generated = false;
  change_game_state(GAME_LOOP_GENERATE_PATTERN);
  turn_on_leds();
}

void game_init(){

    reset_pulsing();

    difficulty_scaling_factor = 1.0 + difficulty_level*0.1;
    print_on_console(String("Scaling F: ") + difficulty_scaling_factor);
    
    score = 0;
    
    print_on_console("Go!"); 
    time_to_display_pattern = MAX_TIME_DISPLAY - (difficulty_level * 500); 
    max_time_to_form_pattern = T3_TIME;
    initPattern();
}


void game_loop_generate_pattern(){
  if (current_time_in_state >= max_time_to_generate_pattern){
      change_game_state(GAME_LOOP_DISPLAY_PATTERN);
  }
  /* generate pattern */
  if(!pattern_generated ){
    for( uint8_t i = 0 ; i < NLEDS ; i++){
      bool quit = false;
      uint8_t n , j;
      do{
          n = random(NLEDS);
          j = 0 ;
          for( ; j < i ; j++){
              if(current_pattern[j] == n){
                  break;
              }
          }
          if( j == i){
              current_pattern[i] = n;
              quit = true;
          }
      } while (!quit); 
    }
    pattern_generated = true;
  }
}

void game_loop_display_pattern(){
    turn_on_pattern(current_pattern, time_to_display_pattern);
    reset_player_input();
    print_on_console(String("Now it's input time... waiting for: ") + max_time_to_form_pattern);
    change_game_state(GAME_LOOP_WAITING_PLAYER_PATTERN);
    turn_off_pattern();
}

void change_to_game_over(){
    print_on_console(String("Game Over - Final Score: ") + score);
    turn_on_led(LED_CTR);
    change_game_state(GAME_OVER);
}


void game_loop_wait_player_pattern(){
  if (current_time_in_state >= max_time_to_form_pattern){
      uint8_t * current_input_pat = get_current_input_pattern();
      bool correct =  true;

      for( int i = 0 ; i < NLEDS && correct ; i++){
        correct = current_input_pat[NLEDS-1-i] == current_pattern[i];
      }

      if (!correct){
        change_to_game_over();
      } else {
        score++;
        time_to_display_pattern -= difficulty_scaling_factor*20;
        if( time_to_display_pattern < MIN_TIME_DISPLAY ) difficulty_scaling_factor=MIN_TIME_DISPLAY; // put a lower limit 
        max_time_to_form_pattern /= difficulty_scaling_factor;
        if (max_time_to_form_pattern < T3_MIN_TIME) max_time_to_form_pattern = T3_MIN_TIME;
        print_on_console(String("New Point! Score ") + score);
        turn_off_pattern();
        initPattern();
      }
  }
}

void game_over(){
  if (current_time_in_state > TIME_IN_GAME_OVER)
  {
      change_game_state(GAME_INTRO);
  }
}

int getState(){
  return game_state;
}

void game_sleep(){
  print_on_console("Going to sleep..");
  reset_pulsing();
  delay(500);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  sleep_disable();   
  change_game_state(GAME_INTRO);
}