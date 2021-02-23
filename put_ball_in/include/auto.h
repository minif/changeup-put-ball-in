#ifndef AUTO    // To make sure you don't declare the function more than once by including the header multiple times.
#define AUTO

void scanMode();
void pickupMode();
void userCtrl();

void takePicture();
extern bool picDebug;
extern int tempx, tempy, piccount, bestx, besty, fc, fps, timerr;
extern int solDist, pickupTime;

extern int gamemode;
const int GM_USER = 0;
const int GM_SCANNING = 1;
const int GM_BALLPICKUP = 2;
extern int xspeed, yspeed, armspeed, inspeed, armctrl;

void steerY();

#endif