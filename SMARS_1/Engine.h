#ifndef __SMARS_ENGINE_H__
#define __SMARS_ENGINE_H__

#include <AFMotor.h>

#define L_MOTOR 3  // Left motor number on the motor shield.
#define R_MOTOR 4  // Right motor number on the motor shield.

// This class provides high level Engine interface for SMARS robot.
class Engine {
  public:
    // Create default SMARS engine.
    Engine();
    
	// Create default SMARS engine using the specified speed scale
	// for left and right motors. The scale must be in the range [0..1]
	Engine(float leftK, float rightK);
	
	
    void accelerate(int delta = 2);
    void turn(int delta = 1);
    void drive(int speed);
    void stop();
  private:

    uint8_t getMotorSpeed(int speed);
    uint8_t getMotorCommand(int speed);
    void    go();
    
    // DATA
    AF_DCMotor d_motorL;
    AF_DCMotor d_motorR;
    
    float      d_tk[2];            // Compensate the motor difference in speed; [0.0..1.0]. Start with 1.0

    float      d_carSpeed;         // Current logical overal speed; -255..255. Negative is reverse.
    float      d_speed[2];         // Current logical speed per motor;
};

#endif