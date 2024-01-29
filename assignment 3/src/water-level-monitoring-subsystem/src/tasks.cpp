#include "tasks.h"

double waterLevel;

void tasks::monitoringTask(void* parameter) { 
    Sonar* pSonar = new Sonar(DIST_ECHO_PIN, DIST_TRIG_PIN, MAXTIME);

  for(;;) {
    waterLevel = pSonar->getDistance();
    delay(100); //frequenza?
  }
}

