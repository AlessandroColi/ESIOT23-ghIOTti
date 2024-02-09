#ifndef __TASKSIMPL__
#define __TASKSIMPL__

#include "devices/Sonar.h"
#include "devices/Led.h"
#include <Arduino.h>
#define DIST_ECHO_PIN 47
#define DIST_TRIG_PIN 48
#define MAXTIME 5000
#define GREEN_LED 38
#define RED_LED 39

extern bool working;
extern long updateFrequence;
extern double waterLevel;

class tasksImpl{

    public:

        static void monitoringTask( void* parameter);
        static void ledControlTask( void* parameter);
};
   
#endif

