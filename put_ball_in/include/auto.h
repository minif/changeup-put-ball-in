#ifndef AUTO    // To make sure you don't declare the function more than once by including the header multiple times.
#define AUTO

void scanMode();
void pickupMode();
void userCtrl();

extern int gamemode;
const int GM_USER = 0;
extern int xspeed, yspeed, armspeed, inspeed, ctrlspeed;

#endif