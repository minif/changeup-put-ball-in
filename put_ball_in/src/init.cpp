/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       init.cpp                                                  */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - User control state                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auto.h"
#include "vex.h"

const int inTime = 50;

int initTimer = inTime;

void initMode() {
  if (Controller1.ButtonB.pressing()) {
    gamemode = GM_USER;
    return;
  }

  Brain.Screen.setCursor(3,3);
  Brain.Screen.print(initTimer);
  armspeed = -127;
  armctrl = -200;
  Brain.Screen.setCursor(4,3);
  Brain.Screen.print("initTimer");
  initTimer--;
  if (initTimer < 40) armspeed = 50;
  if (initTimer < 10) armspeed = 0;
  if (initTimer < 0) gamemode = GM_AUTO;
  Brain.Screen.setCursor(5,3);
  Brain.Screen.print("initTimer");
}