#include "Engine.h"

#include <Arduino.h>

// Comment out to enable the motors. Used for testing the PID
//#define DISABLE_ENGINE

#define MIN_SPEED 0
#define MAX_SPEED 250

// Motor identifiers.
#define LEFT 0
#define RIGHT 1

Engine::Engine()
: d_motorL(3, MOTOR34_64KHZ),
  d_motorR(4, MOTOR34_64KHZ),
  d_carSpeed(0.0)
{
  d_tk[LEFT] = 1.0;     // [0 .. 1] If one of the motors is slower, reduce th
  d_tk[RIGHT] = 0.95;
  
  d_speed[LEFT] = 0.0;
  d_speed[RIGHT] = 0.0;
  
  d_motorL.run(RELEASE);
  d_motorR.run(RELEASE);
}

uint8_t 
Engine::getMotorSpeed(int speed)
{
  if (speed > 0) {
    return map(speed, 1, 255, MIN_SPEED, MAX_SPEED);
  }
  if (speed<0) {
    return map(speed, -1, -255, MIN_SPEED, MAX_SPEED);
  }
  return 0;
}

uint8_t 
Engine::getMotorCommand(int speed)
{
  if (speed > 0) return FORWARD;
  if (speed < 0) return BACKWARD; 
  return RELEASE;
}

void 
Engine::accelerate(int delta)
{
  d_carSpeed += delta;
  d_speed[LEFT]  = constrain(d_carSpeed * d_tk[LEFT],  -255, 255);
  d_speed[RIGHT] = constrain(d_carSpeed * d_tk[RIGHT], -255, 255);
  go();
}

void
Engine::turn(int delta)
{
  d_speed[LEFT]  = constrain(d_carSpeed + delta*d_tk[LEFT],  -255, 255);
  d_speed[RIGHT] = constrain(d_carSpeed - delta*d_tk[RIGHT], -255, 255);
  go();
}

void
Engine::stop()
{
  d_carSpeed = 0;
  d_speed[LEFT] = 0;
  d_speed[RIGHT] = 0;
  go();
}

void
Engine::drive(int speed)
{
  d_carSpeed = speed;
  d_speed[LEFT]  = constrain(speed*d_tk[LEFT],  -255, 255);
  d_speed[RIGHT] = constrain(speed*d_tk[RIGHT], -255, 255);
  go();
}

void
Engine::go()
{ 
#ifndef DISABLE_ENGINE
  d_motorL.setSpeed(getMotorSpeed(d_speed[LEFT]));
  d_motorR.setSpeed(getMotorSpeed(d_speed[RIGHT]));
  d_motorL.run(getMotorCommand(d_speed[LEFT]));
  d_motorR.run(getMotorCommand(d_speed[RIGHT]));
#endif
}
