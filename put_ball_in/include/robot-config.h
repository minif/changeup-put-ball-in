using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor Ldrive;
extern motor Larm;
extern motor Lintake;
extern motor Sintake;
extern motor Rdrive;
extern motor Rarm;
extern motor Rintake;
extern motor Tintake;
extern signature Visions__SIG_1;
extern signature Visions__SIG_2;
extern signature Visions__SIG_3;
extern signature Visions__SIG_4;
extern signature Visions__SIG_5;
extern signature Visions__SIG_6;
extern signature Visions__SIG_7;
extern vision Visions;
extern sonar RangeFinderG;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );