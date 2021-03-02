/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       put.cpp                                                   */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - Ball pickup state                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auto.h"
#include "vex.h"

const int ARMSPEEDFAST = -127;
const int ARMSPEEDSLOW = -20;

const int ARMCTRL_OPEN = -330;

const int XSPEED = 30;

//Ranges for color sensor to see
const int MIDDLE = 150;
const int SMALLRANGE = 30;
const int LARGERANGE = 60;

//Speeds for the robot to move
const int X_SPEED = 60;
const int Y_SPEED = 10;
const int Y_SPEED_FAST = 30;

void Put_setGamemode(int gm) {
  if (gamemode == GM_BALLPICKUP) {
    gamemode = gm;
  }
}

void Put_steerY() {
  if (bestyg>20) {
    if (bestxg<MIDDLE-LARGERANGE) yspeed = Y_SPEED_FAST;
    else if (bestxg<MIDDLE-SMALLRANGE) yspeed = Y_SPEED;
    else if (bestxg<MIDDLE+SMALLRANGE) yspeed = 0;
    else if (bestxg<MIDDLE+LARGERANGE) yspeed = -Y_SPEED;
    else yspeed = -Y_SPEED_FAST;
  } else yspeed = 0;
}

void putMode() {
  armspeed = ARMSPEEDSLOW;
  armctrl = ARMCTRL_OPEN;

  xspeed = XSPEED;

  takePicture();
  Put_steerY();
  
  //if (gamemode != GM_PUT) goneClose = false;
  //if (pickupTime+timeScanning < Brain.timer(timeUnits::sec)) Pickup_setGamemode(GM_SCANNING);
  //if (picDebug) pickup_debug();
}