
#ifndef CHALLENGES_H
#define CHALLENGES_H

//#include <xc.h>
#include "data_sorting.h"  // For switchBMSB and switchDMSB

extern uint8_t taskValueLSB;
//extern uint8_t taskValueMSB;
// prototypes
void challenges();
void getPCLS(); 
void transmitSync(); 
void transmitByte(int byte);  

#endif /* CHALLENGES_H */


