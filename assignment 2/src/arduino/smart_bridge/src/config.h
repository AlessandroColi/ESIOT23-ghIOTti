#ifndef __CONFIG__
#define __CONFIG__

// leds

#define LED01_PIN 0
#define LED02_PIN 0
#define LED03_PIN 0

// sensors and buttons

#define START_BTN 0
#define PIR_PIN 0
#define TEMP_PIN A0
#define DIST_ECHO_PIN 0
#define DIST_TRIG_PIN 0
#define MOTOR_PIN 0
#define LCD_SDA_PIN A0
#define LCD_SCL_PIN A0

// states

#define WAITING_FOR_CAR 1
#define CAR_DETECTED_FOR_CHECK_IN 2
#define ENTERING_WASHING_AREA 3
#define READY_TO_WASH 4
#define WASHING 5
#define LEAVING_WASHING_AREA 6
#define CHECK_OUT 7
#define MAINTENENCE 8


//times and limit values
#define N1 0 //from detected to gate open
#define N2 0 //time that the car is in the correct position for ready wash
#define N3 0 //duration of car wash
#define N4 0 //time that the car is in the correct position for check out

#define MAXTEMP 0 

#define MINDIST 0
#define MAXDIST 0

#endif