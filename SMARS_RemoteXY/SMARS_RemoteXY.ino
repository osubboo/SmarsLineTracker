/*
   SMARS remotely controlled via Wifi using Remote XY mobile application.
   
   This source code of graphical user interface
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.3.3 or later version
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
     - for ANDROID 4.1.1 or later version;
     - for iOS 1.2.1 or later version;

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT
#include <ESP8266WiFi.h>
#include "Engine.h"

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "SMARS_ROBOT"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377

// RemoteXY controls.  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,45,0,8,24,0,
  5,32,24,11,52,52,5,26,31,4,
  160,23,3,53,5,1,26,2,0,1,
  1,15,5,2,26,31,31,79,78,0,
  79,70,70,0,4,32,90,4,5,56,
  6,26 };
  
// this structure defines all the variables of your control interface 
struct {

    // input variable
  int8_t joystick_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_y; // =-100..100 y-coordinate joystick position 
  int8_t balance;    // =-100..100 slider position 
  uint8_t power;     // =1 if switch ON and =0 if OFF 
  int8_t max_speed;  // =-100..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

Engine engine; 

void setup() 
{
  Serial.begin(9600);
  RemoteXY_Init(); 
  
  engine.init();
  engine.stop();
}

void loop() 
{ 
  RemoteXY_Handler ();

  if (RemoteXY.power) {
    engine.set_balance(RemoteXY.balance);
    engine.set_max_speed(RemoteXY.max_speed);
    engine.drive(RemoteXY.joystick_y, RemoteXY.joystick_x);
  } else {
    engine.stop();
  }
}
