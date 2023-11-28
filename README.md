# Embedded System and Internet of Things Assignments
This repository contains our group projects for the Embedded Systems and Internet of Things course within the Bachelor's degree program in Computer Engineering and Science at the University of Bologna. Below, you will find the assignments for the respective projects:

<details>
  <summary>
    <h2>Assignment #1 - Restore the Lights!</h2>
  </summary>
  We want to realise an embedded system implementing a game called Catch the Led Pattern!.
  The game board is based on 4 green leds L1, L2, L3, L4 and red led LS, four tactile buttons B1, B2, B3, B4 and a potentiometer Pot. In the initial state, all green leds are off but led LS that pulses (fading in and out), waiting for some player to start the game. On the serial line, it must be sent the message “Welcome to the Restore the Light Game. Press Key B1 to Start”. 
  
  If/when the button B1 is pressed the game starts.  If the B1 button is not pressed within 10 seconds, the system must go into deep sleeping. The system can be awoken back  by pressing any button. Once awoken, the system goes in the initial state and the led Ls starts pulsing again.  When the game starts, all leds are switched off and a “Go!” message is sent on the serial line. An initial score is set to zero.
  
  During the game:
  the leds L1…L4 are turned on some random time T1 
  then, the leds are then turned off one by one in some random order, taking T2 time 
  the player has max T3 time for restoring the leds in the inverse order, by pressing the buttons B1…B4 (each button Bi turns on the corresponding led Li)
  If the player restores the lights on time and in the correct (inverse) order, then:
  the score is increased and a message "New point! Score: XXX" (where XXX is the current score) is sent on the serial line
  the game goes on, by reducing the times T2 and T3 of some factor F.  
  If the player does not restore the lights on time in the correct order,  then the red led Ls turned on for 1 second and the game ends: a message "Game Over. Final Score: XXX" (where XXX is the final score) is sent on the serial line for 10 seconds, then the game restarts from the initial state.
  
  Before starting the game, the potentiometer Pot device can be used to set the difficulty L level  which could be a value in the range 1..4 (1 easiest, 4 most difficult). The level must affect the value of the factor F (so that the more difficult the game is, the greater the factor F must be). 
</details>

<details open>
  <summary>
    <h2>Assignment #2 - Smart Car-Washing System</h2>
  </summary>
  We want to realise an embedded system called Smart Car-Washing System.
  The prototype  is meant to simulate a simple smart system for car washing.
  The simulated environment involves two main areas: 
  <ul>
    <li>a Check-In/Out Area, welcoming  vehicles that aim at being washed (one by one)</li>
    <li>the Washing Area, which is where the washing process occurs</li>
  </ul>
  When no one is around, the system is off, sleeping. When a vehicle is detected by the CAR PRESENCE DETECTOR in the Check In/Out Area, the light L1 is turned on and on the USER LCD the message: Welcome is displayed. After N1 seconds that a vehicle is in the Check In/Out Area, the gate GATE is opened to allow the vehicle to proceed to the Washing Area and the light L2 starts blinking with a period equals to 0.1 secs. On the USER LCD the message Proceed to the Washing Area is displayed. The entrance of a vehicle in the Washing Area is tracked by the CAR DISTANCE DETECTOR: when the measured distance is less than MINDIST for N2 secs, the vehicle is considered fully entered. The gate GATE is then closed and the light L2 stops blinking and is turned on.  On the USER LCD the message: Ready to Wash is displayed. <br/><br/>
  When the user presses the button START, the simulated washing process begins and lasts for N3 secs. During this time, the light L2 blinks with a period equal to 0.5 secs. On the USER LCD a countdown is displayed–either using numbers or a bar changing dimensions. After N3 secs, the washing process ends: L2 is turned off, L3 is turned on, the message Washing complete, you can leave the area  is displayed on the USER LCD and the gate GATE is opened to allow the vehicle to move away from the Washing Area.  In this stage, the leaving process can be considered completed when the CAR DISTANCE DETECTOR measures a distance greater than MAXDIST for N4 secs. At that point, the gate GATE is closed, L3 is turned off. <br/><br/>
  The PC Console Dashboard is meant to be a simple GUI used by car-washing maintainers to monitor the state and functioning of the washing system and intervene if necessary. In particular:
  <ul><li>It visualises the total number of washes done so far and  the current state of the washing machine. To this purpose, during the washing process the temperature is monitored by means of the TEMP sensor, reporting  the ongoing value on the PC Console Dashboard.</li>
  <li>If the temperature becomes greater than MAXTEMP for N4 seconds, then the washing process  is suspended and a message Maintenance required is displayed on the PC Console Dashboard, along with the message  Detected a Problem - Please Wait on the USER LCD.</li>
  <li>Then, the PC Console Dashboard must provide a button Maintenance done to notify that the problem has been verified (and solved)  and the washing process can go on.</li>
  </ul>
</details>

<details>
  <summary>
    <h2>Assignment #3 - </h2>
  </summary>
  TBA
</details>
