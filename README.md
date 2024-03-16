# Embedded System and Internet of Things Assignments
This repository contains our group projects for the Embedded Systems and Internet of Things course within the Bachelor's degree program in Computer Engineering and Science at the University of Bologna. Below, you will find the assignments for the respective projects:

<details>
  <summary>
    Assignment #1
  </summary>
  
  ## Restore the Lights
  We want to create an embedded system that implements a game called "Catch the Led Pattern" The game board is based on 4 green LEDs (L1, L2, L3, L4), a red LED (LS), 4 tactile buttons (B1, B2, B3, B4) and a potentiometer.
  
  In the initial state, all green LEDs are off, but the LS LED is pulsing (fading in and out), waiting for a player to start the game. If/when button B1 is pressed, the game will start. If button B1 is not pressed within 10 seconds, the system goes into deep sleep. The system can be woken up by pressing any button. Once woken up, the system returns to its initial state and LED Ls starts pulsing again.
  
  During the game LEDs L1...L4 are all switched on and then switched off one by one in a random order for a certain time.
  The player has a maximum of time to switch on the LEDs in reverse order by pressing keys B1...B4 (each key Bi switches on the corresponding LED Li).
  If the player has switched on the lights in time and in the correct (inverse) order, the game continues by reducing the time by a factor called F.  
  If the player does not switch on the lights in the correct order, the red LED L lights up for 1 second and the game ends, then the game restarts from the beginning.
  
  Before starting the game, the difficulty level can be set with the potentiometer. This can be a value in the range 1..4 (1 being the easiest, 4 being the most difficult). The level must have an effect on the value of the factor F (so the more difficult the game, the higher the factor F must be).
</details>

<details>
  <summary>
    Assignment #2
  </summary>

  ## Smart Car-Washing System
  We want to implement an embedded system called the Smart Car-Washing System, which simulates a simple smart car-washing system.
  The simulated environment includes two main areas:
  * a check-in/check-out area, where the cars that want to be washed are received (one by one)
  * the washing area, where the washing process takes place

  When no one is around, the system is off, sleeping. When a vehicle is detected by the presence detector in the check-in/check-out area, the L1 light comes on and the LCD displays the message "Welcome". After N1 seconds of a vehicle being in the check in/out area, the gate will open to allow the vehicle to proceed to the washing area and the L2 light will start flashing with a period equal to 0.1 seconds. The LCD will display the message "Proceed to Wash Area". The entry of a vehicle into the washing area is monitored by the distance detector: if the measured distance is less than a constant value, called MINDIST, for N2 seconds, the vehicle is considered fully entered. The GATE is then closed and the L2 light stops blinking and lights up.  The LCD displays the message "Ready to wash".

  When the user presses the start button, the simulated washing cycle begins and lasts for N3 seconds. During this time the L2 light flashes at 0.5 second intervals. A countdown is displayed on the LCD, either with numbers or with a bar that changes dimensions. After N3 seconds, the washing cycle ends: L2 is switched off, L3 is switched on, the message "Washing completed, you can leave the area" is displayed on the LCD and the gate is opened to allow the vehicle to leave the washing area. At this stage, the exit process can be considered complete when the CAR distance detector measures a distance greater than MAXDIST for N4 seconds. At this point the gate closes and L3 is switched off.
  
  The PC Dashboard Console is intended to be a simple GUI used by the carwash operator to monitor the status and operation of the carwash and to intervene if necessary. In particular: It visualises the total number of washes performed and the current status of the carwash. During the wash, the temperature is monitored by the temperature sensor and the current value is displayed on the dashboard of the PC console. If the temperature rises above MAXTEMP for N4 seconds, the wash will stop and a Service Required message will appear on the PC Console Dashboard and the message "Detected a Problem - Please Wait" will appear on the LCD. The PC Console Dashboard must then provide a Maintenance Done button to indicate that the problem has been checked (and resolved) and the wash can be resumed.
</details>

<details>
  <summary>
    Assignment #3
  </summary>
  
  ## Smart River Monitoring
  The Smart River Monitoring system is designed to monitor the water level of a river and, depending on the level, control a valve to distribute the water to some canals.  More details:
  
  * About the **Water level Monitoring** subsystem: The Water Level Monitoring subsystem is responsible for continuously monitoring the water level using sonar.
The water level is sampled and sent to the River Monitoring Service with a certain frequency F 
This frequency depends on the state of the system and is defined by the River Monitoring Service (see below).
If the system is working correctly (network ok, sending data ok), the green LED is on and the red LED is off; otherwise, if there are network problems, the red LED should be on and the green LED off.
* About the **Water Channel Controller** subsystem: 
The Water Channel Controller subsystem is responsible for controlling the valve that determines how much water should flow to the channels, which is determined by the valve opening level - from 0% = fully closed (no water flows from the river to the channels) to 100% = fully open.
The valve is actuated by the servomotor - angle 0° corresponds to valve opening level 0%, angle 180° corresponds to valve opening level 100%.
The opening level of the valve depends on the state of the system, which is determined by the River Monitoring Service (see below). 
The Water Channel Controller also has a button to enable a manual control mode.
When the button is pressed, the controller enters manual mode so that the valve opening level can be controlled manually by the operator using a potentiometer. To exit the manual mode, press the button again.  
The Water Channel Controller subsystem is also equipped with an LCD display showing the current valve opening level and the current modality (AUTOMATIC or MANUAL).
* About the **River Monitoring Service**: 
This is the subsystem that determines the overall policy and behaviour of the river monitoring system, according to the water levels measured by the water level monitoring subsystem.
Policy:
   * When the water level is in the range [WL1, WL2], the system is considered to be in a NORMAL state. In the NORMAL state
the frequency to be used for monitoring the water level is F1
the valve opening level should be 25%.
  * If the water level is < WL1, the system is in an ALARM-TOO-LOW condition. 
In this state, the valve opening level should be 0%.
   * If the water level is > WL2, there are three other cases
     *  WL2 < water level <= WL3 → the system is in a PRE-ALARM-TOO-HIGH state. 
  In this state, the frequency to be used for monitoring the water level should be increased to F2 (where F2 > F1).
     * WL3 < water level <= WL4 → ALARM-TOO-HIGH condition 
  In this state, the frequency is still F2, but the valve opening level must be 50%.
     * Water level > WL4 → ALARM-TOO-HIGH-CRITICAL condition
In this state the frequency is still F2 but the valve opening level should be 100%.
* About the **River Monitoring Dashboard**: 
The dashboard has two main functions:
  * To visualise the state of the River Monitoring system, in particular: the graph of the evolution of the water level over a given time window (the last N minutes), the state of the system 
  (NORMAL, ALARM TOO LOW, PRE-ALARM TOO HIGH, ALARM TOO HIGH, ALARM TOO HIGH-CRITICAL) and the valve opening level.
  * To allow a user to manually control, from a remote location, the valve opening level.
</details>
