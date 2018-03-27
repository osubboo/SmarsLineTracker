#include "Engine.h"
#include "IR_Sensor.h"

#define KP 0.6     // Proportional
#define KD 0.2     // Differential
#define KI 0.0001  // Integral
#define DT 200     // control loop time interval, in ms.

IR_Sensor sensor(KP, KD, KI);
Engine engine;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Train the sensor array.
  sensor.train(10);

  // Go forward & steer. 
  engine.drive(250);
  int error = 0;
  while (true) {
     sensor.update();
     error = constrain(sensor.getError(), -250, 250);
     engine.turn(-error);
     delay(DT);
  }
}
