/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       usercontrol.cpp                                           */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - User control state                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auto.h"
#include "vex.h"

//Sensitivity used for robot control
int C_INSPEED = 127;
int C_ARMSPEED = 127;
int C_DRIVESPEED = 1;

//States to measure when the buttons are pressed
bool buttonPushingD = false;
bool buttonPushingU = false;

bool buttonPushingUL = false;
bool buttonPushingDL = false;

void userCtrl() {
  //Determine if a button is pressed this cycle
  if (Controller1.ButtonUp.pressing() && !buttonPushingUL) buttonPushingU = true;
  else buttonPushingU = false;

  if (Controller1.ButtonDown.pressing() && !buttonPushingDL) buttonPushingD = true;
  else buttonPushingD = false;

  //User Control
  xspeed = Controller1.Axis3.value();
  yspeed = Controller1.Axis4.value();

  if (Controller1.ButtonR1.pressing()) inspeed = -C_INSPEED;
  else if (Controller1.ButtonR2.pressing()) inspeed = C_INSPEED;
  else inspeed = 0;

  if (Controller1.ButtonL1.pressing()) armspeed = -C_ARMSPEED;
  else if (Controller1.ButtonL2.pressing()) armspeed = C_ARMSPEED;
  else armspeed = 0;

  if (buttonPushingU) armctrl += -64;
  else if (buttonPushingD) armctrl += 64;

  if (Controller1.ButtonA.pressing()) {
    gamemode = GM_SCANNING;
  }

  if (Controller1.ButtonX.pressing()) {
    pickupMode();
  }

  //Remember last input for next cycle
  buttonPushingUL = Controller1.ButtonUp.pressing();
  buttonPushingDL = Controller1.ButtonDown.pressing();
}