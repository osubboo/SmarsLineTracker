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

// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,3,0,1,0,37,0,8,24,1,
  5,0,10,52,44,44,162,24,31,2,
  0,20,4,22,11,134,27,31,31,79,
  78,0,79,70,70,0,66,132,10,17,
  42,33,35,35 }; 
  
// this structure defines all the variables of your control interface 
struct {

  // input variable
  int8_t joystick_1_x; // =-100..100 x-coordinate joystick position 
  int8_t joystick_1_y; // =-100..100 y-coordinate joystick position 
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 

  // output variable
  int8_t level_1; // =0..100 level position 

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

  if (RemoteXY.switch_1) {
    engine.drive(RemoteXY.joystick_1_y, RemoteXY.joystick_1_x);
    RemoteXY.level_1 = map(RemoteXY.joystick_1_y, -100, 100, 0, 100);
  } else {
    engine.stop();
  }
}
