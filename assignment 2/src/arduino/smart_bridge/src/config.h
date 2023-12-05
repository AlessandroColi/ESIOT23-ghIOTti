#ifndef __CONFIG__
#define __CONFIG__

// leds

#define LED01_PIN 8
#define LED02_PIN 3
#define LED03_PIN 4
#define BLINK_INT1 100
#define BLINK_INT2 500

// sensors and buttons

#define START_BTN 5
#define PIR_PIN 2
#define TEMP_PIN A3
#define DIST_ECHO_PIN 11
#define DIST_TRIG_PIN 12
#define MOTOR_PIN 13
#define LCD_SDA_PIN A4
#define LCD_SCL_PIN A5

#define LCD_VCC 13


//times and limit values
#define N1 5000 //from detected to gate open
#define N2 3000 //time that the car is in the correct position for ready wash
#define N3 10000 //duration of car wash
#define N4 3000 //time that the car is in the correct position for check out

#define MAXTEMP 40
#define MINDIST 0.25
#define MAXDIST 0.10

#define MAXTIME 5000 //for distance sensor


#endif