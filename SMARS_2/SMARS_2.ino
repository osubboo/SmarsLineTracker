#include <AFMotor.h>
// SMARS Demo with ultrasonic sensor and adafruit V1 shield

// You'll need an Adafruit Motor shield V1 and a HC-04 sensor

// Motors initialization
AF_DCMotor R_motor(2);         // defines Right motor connector
AF_DCMotor L_motor(1);         // defines Left motor connector

// Change the following values to make the robot  drive as straight as possible
// The valid range is [0..255]  
#define L_SPEED 200
#define R_SPEED 180

// Sensor pins
#define TRIG_PIN  A4
#define ECHO_PIN  A5

void setup() {
  Serial.begin(9600);          // sets up Serial port speed to 9600 bod.

  // Setup pin modes
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  L_motor.setSpeed(L_SPEED);   // set L motor speed
  R_motor.setSpeed(R_SPEED);   // set R motor speed
  
  L_motor.run(RELEASE);        // turn L motor off
  R_motor.run(RELEASE);        // turn R motor off
}

unsigned long get_distance(){  
  // Set the trig pin to HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin, returns the sound wave travel time in microseconds
  // and calculate the distance.
  unsigned long distance = pulseIn(ECHO_PIN, HIGH) * 0.017;  // 0.034/2
  
  // Prints the distance on the Serial Monitor.
  //Serial.print("Distance: ");
  //Serial.println(distance);

  return distance;
}

unsigned long D;
void loop() {
  D = get_distance();
  
  if (D < 10) {                // Obsticle in 10 cm?
    L_motor.run(FORWARD);      // Turn Right
    R_motor.run(RELEASE);
  } else {
    L_motor.run(FORWARD);      // Go straight
    R_motor.run(FORWARD);
  }
  delay(200);
}

