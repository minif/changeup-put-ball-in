#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Ldrive = motor(PORT10, ratio18_1, false);
motor Larm = motor(PORT9, ratio18_1, false);
motor Lintake = motor(PORT12, ratio36_1, false);
motor Sintake = motor(PORT20, ratio18_1, false);
motor Rdrive = motor(PORT1, ratio18_1, false);
motor Rarm = motor(PORT2, ratio18_1, false);
motor Rintake = motor(PORT11, ratio36_1, false);
motor Tintake = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
signature Visions__BBLUE = signature (1, -3101, -391, -1746, 1495, 9135, 5314, 0.9, 0);
signature Visions__RRED = signature (2, 3029, 7281, 5156, -1957, 1, -978, 1.4, 0);
signature Visions__GGREEN = signature (3, -4971, -4519, -4744, -5761, -5055, -5408, 2.5, 0);
vision Visions = vision (PORT5, 50, Visions__BBLUE, Visions__RRED, Visions__GGREEN);
/*vex-vision-config:end*/
sonar Sonar = sonar(Brain.ThreeWirePort.G);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}