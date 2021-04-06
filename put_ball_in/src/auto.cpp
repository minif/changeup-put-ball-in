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

int stage = 0;
int ticks = 0;
bool armUp;

void hardCodedActions() {
  armspeed = 0;
  inspeed = 0;
  inspeed2 = 0;
  armUp = false;
  xspeed = 0;
  yspeed = 0;
  
  ticks--;
  if (ticks < 1) {
    Controller1.Screen.print(stage);
    stage++;
    switch (stage) {
      case 1: 
        gamemode = GM_BALLPICKUP;
        break;
      case 2: 
        ticks = 200;
        xspeed = -50;
        yspeed = 0;
        break;
      case 3: 
        gamemode = GM_PUT;
        break;
      case 4: 
        ticks = 100;
        xspeed = 0;
        yspeed = 127;
        break;
      case 5:
        ticks = 100;
        xspeed = 100;
        yspeed = 0;
        break;
      case 6:
        gamemode = GM_BALLPICKUP;
        break;
      case 7: 
        ticks = 50;
        xspeed = -50;
        yspeed = 0;
        break;
      case 8: 
        gamemode = GM_PUT;
        break;
    }
  }
}

void auto_debug() {
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Autonymouse1       ");
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print(focusOnRed);
}

void autoMode() {
  if (Controller1.ButtonB.pressing()) {
    gamemode = GM_USER;
  }

  takePicture();
  //rotateAround();
  hardCodedActions();

  if (armUp) armspeed = 90 - (Larm.rotation(rotationUnits::deg)/5) ;

  if (picDebug) auto_debug();
}