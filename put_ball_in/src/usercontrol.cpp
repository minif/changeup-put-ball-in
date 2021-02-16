#include "auto.h"
#include "vex.h"

void userCtrl() {
  gamemode = GM_USER;
  xspeed = Controller1.Axis3.value();
  yspeed = Controller1.Axis4.value();

  if (Controller1.ButtonR1.pressing()) inspeed = -127;
  else if (Controller1.ButtonR2.pressing()) inspeed = 127;
  else inspeed = 0;
}