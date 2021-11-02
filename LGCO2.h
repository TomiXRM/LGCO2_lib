/***************************************************************************
   This is a library for the LGCO2 module (MH-Z19 CO2 sensor)

   tomix reqport blog
   If you have any question, visit my twitter and giveme DM
   ------> https://twitter.com/tomixrm/

   These sensors use I2C to communicate, 2 pins are required to interface.

   Written by tomixrm for e-Kagaku.

   MIT license, all text above must be included in any redistribution
***************************************************************************/
#ifndef _LGCO2_
#define _LGCO2_

#include "Arduino.h"
// #define _DEBUG_CO2_

class LGCO2 {
private:
/* data */
int CO2;
char sensorStatus;
void getValue();
public:
LGCO2();

void init();
bool available();
char getStatus();
int read();
operator int();
};
#endif
