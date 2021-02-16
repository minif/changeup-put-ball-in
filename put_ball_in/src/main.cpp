/* ---------------------------------------------------------------------------- */
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Feb  2021                                             */    
/*    Description:  Competition Template                                      */
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
// RangeFinderG         sonar         G, H            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "auto.h"

using namespace vex;

int xspeed, yspeed, armspeed, inspeed, armctrl, gamemode;

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

int armctrlback = 0;

void updateMotors() {
  Ldrive.spin(directionType::fwd,yspeed+xspeed,velocityUnits::rpm);
  Rdrive.spin(directionType::fwd,yspeed-xspeed,velocityUnits::rpm);

  Rintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
  Tintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
  Lintake.spin(directionType::fwd,-inspeed,velocityUnits::rpm);

  Larm.spin(directionType::fwd,armspeed,velocityUnits::rpm);
  Rarm.spin(directionType::fwd,-armspeed,velocityUnits::rpm);

  if (armctrl != armctrlback) {
    armctrlback = armctrl;
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
  // User control code here, inside the loop
  while (1) {

    switch(gamemode) {
      case GM_USER: 
      userCtrl();
      break;
    }

    updateMotors();
    //Brain.Screen.print("no");

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
