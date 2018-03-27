#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <Arduino.h>

class Engine {
  public:
    Engine();
    void init();
    void drive(int8_t speed, int8_t turn);
    void stop();
    
  private:

    uint16_t getMotorSpeed(int speed);
    
    // DATA
    float      d_tk[2];    // Compensate the motor difference in speed; [0.0..1.0]. Start with 1.0
};

#endif
