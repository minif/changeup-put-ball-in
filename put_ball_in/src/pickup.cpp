/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       pickup.cpp                                                */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - Ball pickup state                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auto.h"
#include "vex.h"

//Ranges for color sensor to see
const int MIDDLE = 150;
const int SMALLRANGE = 30;
const int LARGERANGE = 60;

//Ranges for sonar to see
const int BALL_FAR_DIST = 250;
const int BALLDIST = 100;

//Speeds for the robot to move
const int X_SPEED = 30;
const int Y_SPEED = 10;
const int Y_SPEED_FAST = 30;

//Values for intake control
const int IN_SPEED = 128;
const int CTRL_OPEN = -339;
const int CTRL_CLOSE = 50;

//Time to spend scanning
const int timeScanning = 5;

int sonDist, pickupTime; 
bool goneClose = false;

//Set gamemode, remembering to set the close flag to false;
void Pickup_setGamemode(int gm) {
  if (gamemode == GM_BALLPICKUP) {
    goneClose = false;
    gamemode = gm;
  }
}

//Steer the robot based on the y position
void steerY() {
  if (besty>20) {
    if (bestx<MIDDLE-LARGERANGE) yspeed = Y_SPEED_FAST;
    else if (bestx<MIDDLE-SMALLRANGE) yspeed = Y_SPEED;
    else if (bestx<MIDDLE+SMALLRANGE) yspeed = 0;
    else if (bestx<MIDDLE+LARGERANGE) yspeed = -Y_SPEED;
    else yspeed = -Y_SPEED_FAST;
  } else yspeed = 0;
}

void pickup_debug() {
  Brain.Screen.print("     ");
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Picking Up    ");
  Brain.Screen.setCursor(6,1);
    Brain.Screen.print(goneClose);
  Brain.Screen.setCursor(7,1);
  Brain.Screen.print(sonDist);
  Brain.Screen.setCursor(8,1);
  Brain.Screen.print(pickupTime+timeScanning);
  Brain.Screen.setCursor(9,1);
  Brain.Screen.print(Brain.timer(timeUnits::sec));
}

void pickupMode() {
  //Switch back to user control if needed
  if (Controller1.ButtonB.pressing()) Pickup_setGamemode(GM_USER);
  //Scan field
  takePicture();
  sonDist = Sonar.distance(distanceUnits::mm);

  if (sonDist < BALLDIST) {
    //If ball is inside the robot being picked up
    armctrl = CTRL_CLOSE;
    inspeed=IN_SPEED;
    goneClose = true;
  } if (sonDist < BALL_FAR_DIST) {
    //Approaching a ball
    armctrl = CTRL_OPEN;
    inspeed=IN_SPEED;
  } else {
    //Driving to a ball
    Brain.Screen.setCursor(10,1);
    if (goneClose) Pickup_setGamemode(GM_SCANNING);
    else Brain.Screen.print("not gone in yet");
    armctrl = CTRL_OPEN;
    inspeed=0;
    steerY();
  }

  xspeed = X_SPEED;

  if (gamemode != GM_BALLPICKUP) goneClose = false;
  if (pickupTime+timeScanning < Brain.timer(timeUnits::sec)) Pickup_setGamemode(GM_SCANNING);
  if (picDebug) pickup_debug();
}