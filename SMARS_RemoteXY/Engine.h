#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <Arduino.h>

class Engine {
  public:
    Engine();
    void init();
    void set_balance(int8_t balance);
    void set_max_speed(int8_t max_speed);
    void drive(int8_t speed, int8_t turn);
    void stop();
    
  private:

    uint16_t getMotorSpeed(int speed);
    
    // DATA
    float      d_tk[2];    // Compensate the motor difference in speed; [0.0..1.0]. Start with 1.0
    uint16_t   d_max_speed;
};

#endif
