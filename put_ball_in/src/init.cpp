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

const int inTime = 15;

int initTimer = inTime;

void initMode() {
  Brain.Screen.setCursor(3,3);
  Brain.Screen.print(initTimer);
  armspeed = -127;
  armctrl = -200;
  Brain.Screen.setCursor(4,3);
  Brain.Screen.print("initTimer");
  initTimer--;
  if (initTimer < 0) gamemode = GM_USER;
  Brain.Screen.setCursor(5,3);
  Brain.Screen.print("initTimer");
}