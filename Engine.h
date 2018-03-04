#include <AFMotor.h>

class Engine {
  public:
    Engine();
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

