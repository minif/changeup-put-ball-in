/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       scan.cpp                                                  */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - Scan state                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auto.h"
#include "vex.h"

const int MIDDLE = 150;
const int SMALLRANGE = 30;
const int LARGERANGE = 60;

const int Y_SPEED = 30;
const int Y_SPEED_FAST = 30;

void rotateAround() {
  if (besty>20&&ballc > 0) {
    if (bestx<MIDDLE-LARGERANGE) yspeed = Y_SPEED_FAST;
    else if (bestx<MIDDLE-SMALLRANGE) yspeed = Y_SPEED;
    else if (bestx<MIDDLE+SMALLRANGE) {
      pickupTime = Brain.timer(timeUnits::sec);
      gamemode = GM_BALLPICKUP;
    }
    else if (bestx<MIDDLE+LARGERANGE) yspeed = -Y_SPEED;
    else yspeed = -Y_SPEED_FAST;
  } else yspeed = Y_SPEED_FAST*1.4;
}

void scan_debug() {
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Scanning       ");
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print(bestx);
}

void scanMode() {
  if (Controller1.ButtonB.pressing()) {
    gamemode = GM_USER;
  }

  takePicture();
  rotateAround();
  if (picDebug) scan_debug();
}