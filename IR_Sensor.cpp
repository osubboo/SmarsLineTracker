#include "IR_Sensor.h"

#include <Arduino.h>

IR_Sensor::IR_Sensor(float kP, float kD, float kI)
: d_Kp(kP),
  d_Kd(kD),
  d_Ki(kI)
{
}

void IR_Sensor::train(int loops)
{
  loops = constrain(loops, 1, 20);
  
  d_reference = 0;
  for(int loop = 0; loop < loops; ++loop) {
    update();
    
    float average = 0.0;
    for(int i = 0; i < IR_NUM; ++i) {
      average += d_data[i] * SensorW[i];
    }
    d_reference += average / IR_NUM;
    delay(500);
  }
  d_reference /= loops;
  d_integral = 0;
  d_derivative = 0;
  d_last_proportional = 0;
}

void IR_Sensor::update()
{
  for(int i = 0; i < IR_NUM; ++i) {
    d_data[i] = float(constrain(analogRead(SensorPins[i]), 1, 1024));
  }
  //printBar();
}

int
IR_Sensor::getError()
{
  float average = 0.0;
  
  for(int i = 0; i < IR_NUM; ++i) {
    average += d_data[i] * SensorW[i]; 
  }
  float position = average / IR_NUM;

  float proportional = position - d_reference;
  
  d_integral += proportional;
  d_derivative = proportional - d_last_proportional;
  d_last_proportional = proportional; 
  
  int error_value = constrain(int(proportional * d_Kp + d_integral * d_Ki + d_derivative * d_Kd), -255, 255);
  
  return error_value;
}

void IR_Sensor::printBar() 
{
  String bar = String("Sensors: "); // empty the string
  // read the sensors and add them to the string
  bar = bar + d_data[0] + ' ' + d_data[1] + ' ' + d_data[2] + ' ' + d_data[3] + ' ' + d_data[4];
  Serial.println(bar);
}

