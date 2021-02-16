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
vision Visions = vision (PORT5, 50);
/*vex-vision-config:end*/
sonar RangeFinderG = sonar(Brain.ThreeWirePort.G);

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