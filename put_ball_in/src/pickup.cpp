#include "auto.h"
#include "vex.h"

const int MIDDLE = 150;
const int SMALLRANGE = 30;
const int LARGERANGE = 60;

const int BALL_FAR_DIST = 400;
const int BALLDIST = 100;

const int X_SPEED = 30;
const int Y_SPEED = 30;
const int Y_SPEED_FAST = 30;

const int IN_SPEED = 128;
const int CTRL_SPEED = 64;

int sonDist;

void steerY() {
  if (besty>20) {
    if (bestx<MIDDLE-LARGERANGE) yspeed = Y_SPEED_FAST;
    else if (bestx<MIDDLE-SMALLRANGE) yspeed = Y_SPEED;
    else if (bestx<MIDDLE+SMALLRANGE) yspeed = 0;
    else if (bestx<MIDDLE+LARGERANGE) yspeed = -Y_SPEED;
    else yspeed = -Y_SPEED_FAST;
  } else yspeed = 0;
}

void pickupMode() {
  if (Controller1.ButtonB.pressing()) {
    gamemode = GM_USER;
  }

  takePicture();

  sonDist = Sonar.distance(distanceUnits::mm);
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(sonDist);
  Brain.Screen.print("     ");

  if (sonDist < BALLDIST) {
    armctrl = CTRL_SPEED;
    inspeed=CTRL_SPEED;

  } else if (sonDist < BALL_FAR_DIST) {
    armctrl = -CTRL_SPEED/2;
    inspeed=CTRL_SPEED;
  } else {
    armctrl = -CTRL_SPEED;
    inspeed=0;
  }

  xspeed = X_SPEED;

}