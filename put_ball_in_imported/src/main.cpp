#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
//vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int gamemode;

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
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

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

int x,y,xl,yl;

int piccount=0;
int bestx=100;
int tempx;
int besty=100;
int tempy;

int fc = 0;
int fps = 0;
int timerr = 0;

void findbestx(int index) {
    tempx = 0;
    for (int i=0; i<piccount; i++) {
        tempx+=bestx;
    }
    tempx+=Visions.objects[index].centerX;
    piccount++;
    bestx=(tempx)/piccount;
    
}

void findbesty(int index) {
    tempy = 0;
    for (int i=0; i<piccount; i++) {
        tempy+=besty;
    }
    tempy+=Visions.objects[index].centerY;
    piccount++;
    besty=(tempy)/piccount;
    
}

void takePicture(void) {
    Visions.takeSnapshot(BL);
    for (int i=0; i<Visions.objectCount; i++) {
        x = Visions.objects[i].originX;
        y = Visions.objects[i].originY;
        xl = x+ Visions.objects[i].width;
        yl = y+ Visions.objects[i].height;
        Brain.Screen.drawRectangle(x,y,xl,yl,color::blue);
        findbestx(i);
        findbesty(i);
    }
    
     Visions.takeSnapshot(RE);
    for (int i=0; i<Visions.objectCount; i++) {
        x = Visions.objects[i].originX;
        y = Visions.objects[i].originY;
        xl = x+ Visions.objects[i].width;
        yl = y+Visions.objects[i].height;
        Brain.Screen.drawRectangle(x,y,xl,yl,color::red);
        findbestx(i);
        findbesty(i);
    }
}

int xspeed, yspeed, sonDist, ctrlCheck;
int inspeed = 0;
int armspeed = 0;
int ctrlspeed = 0;

int WALLDIST = 150; //About 150
int BALLDIST = 100; 

const int DRIVERGAMEMODE = 0;
const int SEARCHINGGAMEMODE = 1;
const int COLLECTINGGAMEMODE = 2;
const int PUTTINGGAMEMODE = 3;
const int LEGACY = 4;

void driveMode() {
    gamemode = LEGACY;
}

void searchMode() {
    
}

void collectMode() {
    
}

void putMode() {
    
}

void setMotors() {
    Brain.Screen.setCursor(9,1);
              Brain.Screen.print("works");
     Ldrive.spin(directionType::fwd,yspeed+xspeed,velocityUnits::rpm);
      Rdrive.spin(directionType::fwd,yspeed-xspeed,velocityUnits::rpm);
      
      Rintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
      Tintake.spin(directionType::fwd,inspeed,velocityUnits::rpm);
      Lintake.spin(directionType::fwd,-inspeed,velocityUnits::rpm);
      
      Larm.spin(directionType::fwd,armspeed,velocityUnits::rpm);
      Rarm.spin(directionType::fwd,-armspeed,velocityUnits::rpm);
       Brain.Screen.print("spun");
      ctrlCheck = Ddd.rotation(rotationUnits::deg);
    Brain.Screen.print("check");
      ctrlCheck+=(ctrlspeed);
          
      if (ctrlCheck<0&&ctrlCheck>-400) {
          Ddd.rotateTo(ctrlCheck,rotationUnits::deg);
      }
    Brain.Screen.print("rotate");
}

void drawDebug() { 
     Brain.Screen.setCursor(1,1);
      Brain.Screen.print(piccount);
      Brain.Screen.setCursor(5,1);
      Brain.Screen.print(besty);
      Brain.Screen.setCursor(3,1);
      Brain.Screen.print(Sonar.distance(distanceUnits::mm));
      Brain.Screen.setCursor(4,1);
      Brain.Screen.print(Ddd.rotation(rotationUnits::deg));
      
       Brain.Screen.setCursor(7,1);
              Brain.Screen.print(ctrlspeed);
      Brain.Screen.setCursor(8,1);
              Brain.Screen.print(ctrlCheck);
    Brain.Screen.setCursor(10,1);
              Brain.Screen.print(gamemode);
}

void mainLoop() {
    Brain.Screen.clearScreen(color::black);
    takePicture();
      fc++;
      
      if (Brain.timer(timeUnits::sec)>timerr+1) {
          fps = fc;
          fc = 0;
          timerr = Brain.timer(timeUnits::sec);
          piccount=0;
          bestx=0;
          besty=0;
      }
      
      if (Controller1.ButtonR1.pressing()) inspeed = -127;
      else if (Controller1.ButtonR2.pressing()) inspeed = 127;
      else inspeed = 0;
      
      if (Controller1.ButtonUp.pressing()) ctrlspeed = -64;
      else if (Controller1.ButtonDown.pressing()) ctrlspeed = 64;
      else ctrlspeed = 0;
      
      if (Controller1.ButtonL1.pressing()) armspeed = -127;
      else if (Controller1.ButtonL2.pressing()) armspeed = 127;
      else armspeed = 0;
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print(fc);
      
      xspeed = Controller1.Axis3.value();
      yspeed = Controller1.Axis4.value();
       //Brain.Screen.setCursor(6,1);
      if (Controller1.ButtonA.pressing()) {
          sonDist = Sonar.distance(distanceUnits::mm);
          if (besty>20){
            if (bestx<150) yspeed=10;
            else yspeed=-10;
         } else {
          yspeed=0;
        }
          inspeed=128;
      xspeed=30;
          if (sonDist<BALLDIST) {
              ctrlspeed = 64;
             // armspeed = 64;
          } else if (sonDist < 400) {
              ctrlspeed = -32;
          } else {
               ctrlspeed = -64;
          }
      }
}

void usercontrol( void ) {
  // User control code here, inside the loop
    Brain.setTimer(0,timeUnits::sec);
    gamemode = DRIVERGAMEMODE;
  while (1){
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    
     //Draw 
     switch (gamemode) {
         case DRIVERGAMEMODE: driveMode(); break;
         case SEARCHINGGAMEMODE: searchMode(); break;
         case COLLECTINGGAMEMODE: collectMode(); break;
         case PUTTINGGAMEMODE: putMode(); break;
         case LEGACY:  mainLoop(); break;
     }
     //Move 
      drawDebug();
     setMotors();
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}