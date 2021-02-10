#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
//
using namespace vex;
vex::brain Brain;
vex::motor Rdrive (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor Rarm (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor Tintake (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::vision::signature BL (1, -3073, -2195, -2634, 7239, 10543, 8890, 1.2999999523162842, 0);
vex::vision::signature RE (2, 3111, 7241, 5176, -745, 271, -238, 1.2, 0);
vex::vision::signature SIG_3 (3, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision Visions (vex::PORT5, 50, BL, RE, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
vex::motor Larm (vex::PORT9, vex::gearSetting::ratio18_1,false);
vex::motor Ldrive (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::motor Rintake (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor Lintake (vex::PORT12, vex::gearSetting::ratio18_1,false);
vex::motor Ddd (vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::sonar Sonar( Brain.ThreeWirePort.G);
vex::controller Controller1;
vex::competition Competition;