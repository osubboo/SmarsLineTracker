#include "Engine.h"
#include <Arduino.h>

/* define nodemcu motor control pins */
int leftMotorSpeed  = 5;   /* GPIO05(D1) -> IN1  */
int leftMotorDir    = 0;   /* GPIO00(D3) -> IN2  */

int rightMotorSpeed = 4;   /* GPIO04(D2) -> IN3  */
int rightMotorDir   = 2;   /* GPIO02(D7) -> IN4  */

// Motor identifiers.
#define LEFT 0
#define RIGHT 1

Engine::Engine()
{
  d_tk[LEFT] = 1.0;     // [0 .. 1] If one of the motors is slower, reduce tk
  d_tk[RIGHT] = 0.95;
}

void
Engine::init()
{
  pinMode(leftMotorSpeed,  OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
  pinMode(leftMotorDir,    OUTPUT);
  pinMode(rightMotorDir,   OUTPUT);
}

void Engine::set_balance(int8_t balance)
{
  if (balance == 0) {
    d_tk[LEFT]  = 1.0;
    d_tk[RIGHT] = 1.0;
    return;
  }
  
  if(balance < 0) {
    d_tk[LEFT] = 1.0 + (float)balance/500.0;
  } else {
    d_tk[RIGHT] = 1.0 - (float)balance/500.0;
  }
}

void Engine::set_max_speed(int8_t max_speed)
{
  d_max_speed = map(max_speed, -100, 100, 800, 1024);
}

uint16_t 
Engine::getMotorSpeed(int speed)
{
  if (abs(speed) >= 10) {
    return map(abs(speed), 10, 100, 500, d_max_speed);
  }
  return 0;
}

void Engine::drive(int8_t speed, int8_t turn)
{
  int8_t lSpeed = constrain(speed + turn, -100, 100);
  int8_t rSpeed = constrain(speed - turn, -100, 100);

  if (getMotorSpeed(lSpeed) == 0) {
    digitalWrite(leftMotorSpeed, LOW);
    digitalWrite(leftMotorDir,   LOW);
  } else {
    analogWrite(leftMotorSpeed, getMotorSpeed(lSpeed)*d_tk[LEFT]);
    digitalWrite(leftMotorDir, lSpeed > 0 ? HIGH : LOW);
  }

  if (getMotorSpeed(rSpeed) == 0) {
    digitalWrite(rightMotorSpeed, LOW);
    digitalWrite(rightMotorDir,   LOW);
  } else {
    analogWrite(rightMotorSpeed, getMotorSpeed(rSpeed)*d_tk[RIGHT]);
    digitalWrite(rightMotorDir, rSpeed > 0 ? HIGH : LOW);
  }
}

void Engine::stop()
{
  digitalWrite(leftMotorSpeed,  LOW);
  digitalWrite(leftMotorDir,    LOW);
  digitalWrite(rightMotorSpeed, LOW);
  digitalWrite(rightMotorDir,   LOW);
}


