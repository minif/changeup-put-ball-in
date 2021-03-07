/* -------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Minif                                                     */
/*    Created:      Feb 2021                                                  */    
/*    Description:  Vex Robotics Changeup - Main state loops                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Ldrive               motor         10              
// Larm                 motor         9               
// Lintake              motor         12              
// Sintake              motor         20              
// Rdrive               motor         1               
// Rarm                 motor         2               
// Rintake              motor         11              
// Tintake              motor         4               
// Visions              vision        5               
// Sonar                sonar         G, H            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auto.h"

using namespace vex;

//Main motor variables
int xspeed, yspeed, armspeed, inspeed, armctrl, gamemode;

//Ranges for intake control motor
const int inControlMin = -350;
const int inControlMax = 0;

//Average limitation
const int picmax = 150;
const int denoise = 4;

//Variables for camera
int tempx, tempy, piccount, bestx, besty, fc, fps, timerr, ballc;
int bestxr, bestyr, piccountr;
int bestxg, bestyg, piccountg;
int bestxb, bestyb, piccountb;
bool focusOnRed;
bool picDebug;

//Debug
bool disableMotors;

//Init camera variables
void initCamera() {
  piccount = 0;
  bestx = 100; //100 is about center
  besty = 100;
  bestxg = 100;
  bestyg = 100;
  piccountg = 0;
  fc = 0;
  timerr = Brain.timer(timeUnits::sec);
}

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  armctrl = 0;
  picDebug = true;
  initCamera();

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int x, xl, y, yl; // Variables for drawing debug

int counter;

void picDebugPrint(int color) {
  if (picDebug) {
    for (int i=0; i<Visions.objectCount; i++) {
      x = Visions.objects[i].originX;
      y = Visions.objects[i].originY;
      xl = x+ Visions.objects[i].width;
      yl = y+ Visions.objects[i].height;
      switch (color) {
        case 0: Brain.Screen.drawRectangle(x,y,xl,yl,color::red); break;
        case 1: Brain.Screen.drawRectangle(x,y,xl,yl,color::green); break;
        case 2: Brain.Screen.drawRectangle(x,y,xl,yl,color::blue); break;
      }
    }
  }
}

//Find average x and y for each color
void averageRed() {
  tempx = 0;
  tempy = 0;
  counter = 0;
  for (int i=0; i<denoise; i++) {
    Visions.takeSnapshot(Visions__RRED);
    if (Visions.largestObject.exists) counter++;
    tempx += Visions.largestObject.originX;
    tempy += Visions.largestObject.originY;
  }
  bestxr = tempx / denoise;
  bestyr = tempy / denoise;

  if (counter < 2) {
    bestxr = 0;
    bestyr = 0;
  }

  picDebugPrint(0);
}

void averageBlue() {
  tempx = 0;
  tempy = 0;
  for (int i=0; i<denoise; i++) {
    Visions.takeSnapshot(Visions__BBLUE);
    if (Visions.largestObject.exists) counter++;
    tempx += Visions.largestObject.originX;
    tempy += Visions.largestObject.originY;
  }
  bestxb = tempx / denoise;
  bestyb = tempy / denoise;

  if (counter < 2) {
    bestxb = 0;
    bestyb = 0;
  }

  picDebugPrint(2);
}

void averageGreen() {
  tempx = 0;
  tempy = 0;
  for (int i=0; i<denoise; i++) {
    Visions.takeSnapshot(Visions__GGREEN);
    if (Visions.largestObject.exists) counter++;
    tempx += Visions.largestObject.originX;
    tempy += Visions.largestObject.originY;
  }
  bestxg = tempx / denoise;
  bestyg = tempy / denoise;

  if (counter < 2) {
    bestxg = 0;
    bestyg = 0;
  }

  picDebugPrint(1);
}

//Take a picture with color sensor
void takePicture() {
  if (picDebug) Brain.Screen.clearScreen();
  averageRed();
  averageBlue();
  averageGreen();

  if (focusOnRed) {
    bestx = bestxr;
    besty = bestyr;
  } else {
    bestx = bestxb;
    besty = bestyb;
  }
}

int armctrlback = 0;

//Update all the motors
void updateMotors() {
  if (disableMotors) return;
  Ldrive.spin(directionType::fwd,yspeed+xspeed,velocityUnits::rpm);
  Rdrive.spin(directionType::fwd,yspeed-xspeed,velocityUnits::rpm);

  Rintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
  Tintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
  Lintake.spin(directionType::fwd,-inspeed,velocityUnits::rpm);

  Larm.spin(directionType::fwd,armspeed,velocityUnits::rpm);
  Rarm.spin(directionType::fwd,-armspeed,velocityUnits::rpm);

  //Check if intake arm control is within specified range
  if (armctrl < inControlMin) {
    armctrl = inControlMin;
  } else if (armctrl > inControlMax) {
    armctrl = inControlMax;
  }

  if (armctrl != armctrlback) {
    armctrlback = armctrl;
    Sintake.rotateTo(armctrl,rotationUnits::deg);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  //Init before loop
  if (Controller1.ButtonDown.pressing()) disableMotors = true;
  else disableMotors = false;
  gamemode = GM_INIT;
  // User control code here, inside the loop
  while (1) {
    //Robot state manager
    switch(gamemode) {
      //User control state
      case GM_USER: 
        userCtrl();
        break;

      //Ball scanning state
      case GM_SCANNING: 
        scanMode();
        break;

      //Ball pickup state
      case GM_BALLPICKUP: 
        pickupMode();
        break;

      case GM_INIT:
        initMode();
        break;

      case GM_PUT:
        putMode();
        break;
    }

    updateMotors();

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
