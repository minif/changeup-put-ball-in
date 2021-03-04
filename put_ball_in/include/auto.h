/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       auto.h                                                    */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - Main header file                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef AUTO
#define AUTO

//Game states
void scanMode();
void pickupMode();
void userCtrl();
void initMode();
void putMode();

//Picture and sensor related
void takePicture();
extern bool picDebug;
extern int tempx, tempy, piccount, bestx, besty, fc, fps, timerr, ballc;
extern int solDist, pickupTime;
extern int bestxg, bestyg, piccountg;

//Gamestate related
extern int gamemode;
const int GM_USER = 0;
const int GM_SCANNING = 1;
const int GM_BALLPICKUP = 2;
const int GM_INIT = 3;
const int GM_PUT = 4;

//Motor related
extern int xspeed, yspeed, armspeed, inspeed, armctrl;

//Debuug
extern bool disableMotors;

#endif