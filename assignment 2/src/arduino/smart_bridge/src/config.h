#ifndef __CONFIG__
#define __CONFIG__

// leds

#define LED01_PIN 0
#define LED02_PIN 1
#define LED03_PIN 2

// sensors and buttons

#define START_BTN 0
#define PIR_PIN 0
#define TEMP_PIN A0
#define DIST_ECHO_PIN 0
#define DIST_TRIG_PIN 0
#define MOTOR_PIN 0
#define LCD_SDA_PIN A0
#define LCD_SCL_PIN A0


//times and limit values
#define N1 0 //from detected to gate open
#define N2 0 //time that the car is in the correct position for ready wash
#define N3 0 //duration of car wash
#define N4 0 //time that the car is in the correct position for check out

#define MAXTEMP 0 
#define MAXTIME 10000
#define MINDIST 0
#define MAXDIST 0

#endif