#include "tasks.h"
#include "main.cpp"

double waterLevel;

void tasks::monitoringTask(void* parameter) { 
  Sonar* pSonar = new Sonar(DIST_ECHO_PIN, DIST_TRIG_PIN, MAXTIME);

  for(;;) {
    waterLevel = pSonar->getDistance();
    delay(100); //frequenza?
  }
}

void tasks::ledControlTask(void* parameter){
  Led* greenLed = new Led(GREEN_LED);
  Led* redLed = new Led(RED_LED);

  for(;;) {
      if(working){
        greenLed->switchOn();
        redLed->switchOff();    
      }
      else{
        greenLed->switchOff();
        redLed->switchOn(); 
      }
  }

}


