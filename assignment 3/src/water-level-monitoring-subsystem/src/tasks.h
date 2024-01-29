#include "devices/Sonar.h"
#include "devices/Led.h"
#include <Arduino.h>
#define DIST_ECHO_PIN 11
#define DIST_TRIG_PIN 12
#define MAXTIME 5000
#define GREEN_LED 38
#define RED_LED 39
#define SONAR 37

class tasks {

public:
    static void monitoringTask( void* parameter);
    static void ledControlTask( void* parameter);

};
