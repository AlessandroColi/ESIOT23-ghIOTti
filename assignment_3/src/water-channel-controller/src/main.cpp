#include <Arduino.h>
#include "model/WaterController.h"
#include "scheduler/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/StateTask.h"
#include "tasks/ValveTask.h"
#include "tasks/ComunicationTask.h"
#include "config.h"

Scheduler scheduler;
WaterController* waterController;
Lcd* lcd;
Button* button;
Potentiometer* potentiometer;
ServoMotor* servoMotor;
bool automatic = false;
int valvePosition = 0;

void setup() {
  scheduler.init(200);

  Serial.begin(9600);

  servoMotor = new ServoMotorImpl(SERVO_PIN);
  potentiometer = new Potentiometer(POT_PIN);
  lcd = new Lcd();
  button = new ButtonImpl(BUTTON_PIN);

  waterController = new WaterController(button, servoMotor, lcd);

  Task* stateTask = new StateTask(waterController);
  Task* valveTask = new ValveTask(servoMotor, potentiometer, lcd, waterController); // Replace ValveTask with ValveTaskImpl
  Task* comunicationTask = new ComunicationTask(waterController);

  valveTask->init(200);
  stateTask->init(200);
  comunicationTask->init(200);

  scheduler.addTask(valveTask);
  scheduler.addTask(stateTask);
  scheduler.addTask(comunicationTask);
}

void loop() {
  scheduler.schedule();
}