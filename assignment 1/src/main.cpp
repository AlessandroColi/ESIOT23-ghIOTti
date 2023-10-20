#include <Arduino.h>

#include "config.h"
#include "game_core.h"
#include "user_console.h" 
#include "led_board.h"

/*this assignments has been done as a group by:
 Coli Alessandro: alessandro.coli2@studio.unibo.it
 Giangiulli Chiara: chiara.giangiulli@studio.unibo.it
 Pisoni Giovanni: giovanni.pisoni@studio.unibo.it
 Terenzi Mirco: mirco.terenzi@studio.unibo.it
 
 Link for the demonstration video: 
 https://liveunibo-my.sharepoint.com/:f:/g/personal/giovanni_pisoni_studio_unibo_it/ErnLzV7NiVJJmyPk6DCJzkkB3Ns6Jg9OxxFI11XQjZMZQw?e=BbwlHq
 */

void setup() {
  init_player_console();
  init_led_board();
  change_game_state(GAME_INTRO);
  randomSeed(analogRead(POT_PIN)); //use the potentiometer value to generate the seed for better random values
}

void loop(){ 
  update_game_state_time();

    switch (game_state)
    {
    case GAME_INTRO:
      game_intro();
      break;
    case GAME_WAIT_TO_START:
      game_wait_to_start();
      break;
    case GAME_INIT:
      game_init();
      break;
    case GAME_LOOP_GENERATE_PATTERN:
      game_loop_generate_pattern();
      break;
    case GAME_LOOP_DISPLAY_PATTERN:
      game_loop_display_pattern();
      break;
    case GAME_LOOP_WAITING_PLAYER_PATTERN:
      game_loop_wait_player_pattern();
      break;
    case GAME_OVER:
      game_over();
      break;
    case GAME_SLEEP:
      game_sleep();
      break;
    }
}