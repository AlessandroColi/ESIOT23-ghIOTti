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

void setup() {
  scheduler.init(100);

  Serial.begin(9600);

  servoMotor = new ServoMotorImpl(SERVO_PIN);
  potentiometer = new Potentiometer(POT_PIN);
  lcd = new Lcd();
  button = new ButtonImpl(BUTTON_PIN);

  waterController = new WaterController(button, servoMotor, lcd, potentiometer);

  Task *valveTask = new ValveTask(waterController);
  Task* stateTask = new StateTask(waterController);
  Task* comunicationTask = new ComunicationTask(waterController);

  stateTask->init(300);
  valveTask->init(500);
  comunicationTask->init(1000);

  scheduler.addTask(comunicationTask);
  scheduler.addTask(stateTask);
  scheduler.addTask(valveTask);
}

void loop() {
  scheduler.schedule();
}