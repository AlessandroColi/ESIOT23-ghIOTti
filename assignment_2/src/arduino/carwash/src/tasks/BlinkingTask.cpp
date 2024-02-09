#include "BlinkingTask.h"

BlinkingTask::BlinkingTask(int pin){
  this->pin = pin;    
}
  
void BlinkingTask::init(int period){
  Task::init(period);
  led = new Led(pin); 
  state = OFF;
}
  
void BlinkingTask::tick(){
  switch (state){
    case OFF:
      led->switchOn();
      state = ON; 
      break;
    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}