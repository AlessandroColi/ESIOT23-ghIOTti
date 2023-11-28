#ifndef __CONFIG__
#define __CONFIG__

// leds

#define LED01_PIN 2
#define LED02_PIN 3
#define LED03_PIN 4
#define BLINK_INT1 0.1
#define BLINK_INT2 0.5

// sensors and buttons

#define START_BTN 5
#define PIR_PIN 8
#define TEMP_PIN A3
#define DIST_ECHO_PIN 11
#define DIST_TRIG_PIN 10
#define MOTOR_PIN 9
#define LCD_SDA_PIN A4
#define LCD_SCL_PIN A5


//times and limit values
#define N1 5000 //from detected to gate open
#define N2 3000 //time that the car is in the correct position for ready wash
#define N3 10000 //duration of car wash
#define N4 3000 //time that the car is in the correct position for check out

#define MAXTEMP 40
#define MAXTIME 10000
#define MINDIST 0.1
#define MAXDIST 0.3

#endif