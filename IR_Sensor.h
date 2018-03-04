#ifndef __IR_SENSOR_H__
#define __IR_SENSOR_H__

#include <arduino.h>

#define IR_NUM 5
static int SensorPins[IR_NUM] = { A0, A1, A2, A3, A4 };
static float SensorW[IR_NUM] = { -3.0, -2.0, 1.0 , 2.0, 3.0 };

class IR_Sensor
{
  public:
    IR_Sensor(float kP, float kD, float kI);
    void train(int loops);
    void update();
    int getError();
    void printBar();

  private:
    // Inputs for PID control.
    float d_data[IR_NUM];
    float d_Kp;
    float d_Kd;
    float d_Ki;

    // PID variables
    float d_reference;
    float d_integral;
    float d_derivative;
    float d_last_proportional;
};

#endif // __IR_SENSOR_H__

