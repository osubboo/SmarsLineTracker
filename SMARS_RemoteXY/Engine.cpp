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

uint16_t 
Engine::getMotorSpeed(int speed)
{
  if (abs(speed) >= 10) {
    return map(abs(speed), 10, 100, 200, 1000);
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


