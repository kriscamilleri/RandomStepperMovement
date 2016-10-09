// RandomStepperMovement
// -*- mode: C++ -*-
//
// Kris Camilleri, for Samuel Sultana - October 2016
// Requires Arduino, Adafruit Motor Shield v1, and Stepper Motor

#include <AFMotor.h>
#include <AccelStepper.h>
#include <TimerObject.h>

// number of steps, Port number (m1/2 = Port1, m3/4 = Port2)
AF_Stepper motor(200, 2);
int i = 1;

float moveSpeed = 1;
float moveAcceleration = 20;
float duration = 1;
int direction = 1;

int maxSpeed = 200;
int minSpeed = 10;
int minDuration = 10;
int maxDuration = 60;
int minAcceleration = 10;
int maxAcceleration = 180;

TimerObject *timer = new TimerObject(1000);

// method for AccelStepper and Adafruit Motor Shield v1
void forwardstep() {
  motor.onestep(FORWARD, INTERLEAVE);
}
void backwardstep() {
  motor.onestep(BACKWARD, INTERLEAVE);
}

// AccelStepper object mapped to motor shield
AccelStepper stepper(forwardstep, backwardstep);

void setup()
{
  timer->setOnTimer(setNewValues);
  timer->Start();
  Serial.begin(9600);

  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(moveAcceleration);
}

void setNewValues() {
  stepper.runToNewPosition(200);
  moveSpeed = newDirection() * newSpeed();
  duration = newDuration();
  moveAcceleration = newAcceleration();
  stepper.setAcceleration(moveAcceleration);
  stepper.setSpeed(moveSpeed);
  timer->setInterval(duration);

  Serial.println(moveSpeed);
  Serial.print(" - speed");
  Serial.println();
  Serial.println(duration);
  Serial.print(" - duration");
}

void loop()
{
  timer->Update();
  stepper.runSpeed();
}

float newAccelaration() {
  float r = random(minAcceleration, maxAcceleration);
  return r;
}

float newSpeed() {
  float r = random(minSpeed, maxSpeed);
  return r;
}

float newDirection() {
  float r = random(1, 3);
  if (r == 1) {
    return 1.0;
  }
  else if (r == 2) {
    return -1.0;
  }
  return 0;
}

float newAcceleration() {
  float r = random(minAcceleration, maxAcceleration);
  return r;
}


float newDuration() {
  float r = random(minDuration, maxDuration);
  r = r * 1000;
  return r;
}
