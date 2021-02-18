#include "auto.h"
#include "vex.h"

int C_INSPEED = 127;
int C_ARMSPEED = 127;
int C_DRIVESPEED = 1;

bool buttonPushingU = false;
bool buttonPushingD = false;

bool buttonPushingUL = false;
bool buttonPushingDL = false;

void userCtrl() {
  //User Control
  xspeed = Controller1.Axis3.value();
  yspeed = Controller1.Axis4.value();

  if (Controller1.ButtonR1.pressing()) inspeed = -C_INSPEED;
  else if (Controller1.ButtonR2.pressing()) inspeed = C_INSPEED;
  else inspeed = 0;

  if (Controller1.ButtonL1.pressing()) armspeed = -C_ARMSPEED;
  else if (Controller1.ButtonL2.pressing()) armspeed = C_ARMSPEED;
  else armspeed = 0;

  if (Controller1.ButtonUp.pressing() && !buttonPushingUL) buttonPushingU = true;
  else buttonPushingU = false;

  if (Controller1.ButtonDown.pressing() && !buttonPushingDL) buttonPushingD = true;
  else buttonPushingD = false;

  if (buttonPushingU) armctrl = -64;
  else if (buttonPushingD) armctrl = 64;
  else armctrl = 0;

  if (Controller1.ButtonA.pressing()) {
    gamemode = GM_BALLPICKUP;
  }

  buttonPushingUL = Controller1.ButtonUp.pressing();
  buttonPushingDL = Controller1.ButtonDown.pressing();
}