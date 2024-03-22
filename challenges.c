
#include "challenges.h"
#include "data_sorting.h"
#include <xc.h>

void challenges(){

// IR SENSOR CHALLENGE
// SWB to turn on IR sensor
    if(switchBMSB == 0x20) // 2000 means switch up, LSB always 00
    {
            TRISBbits.TRISB1 = 1; //RB1 input
            TRISCbits.TRISC2 = 1; //RC2 output
            ANSELBbits.ANSB1 = 0; //RB1 is digital input
    
    if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
        {
            LATCbits.LATC2 = 0; // necessary?
        }
    }

// LASER TURRET DEFENSE CHALLENGE
// SWD to send shield code
    if (switchDMSB == 0x20){ // if SWD  = 0x2000, LSB always 0x00
        
        getPCLS(); // will give shield code flag status
    
        if (shieldCodeFlag != 0){ // A value of !0 means there is a shield code loaded
            
            transmitSync(); // sync bytes
            
            transmitByte(0x02); // MSG ID
            
            transmitByte(0x09); // MSG ID
            
            transmitByte(0x01); // Payload LSB
            
            transmitByte(0x00); // Payload MSB
            
        }    
    }
}
