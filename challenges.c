#include "challenges.h"
#include "data_sorting.h"
#include <xc.h>

int potentiometerA;

void challenges(){
    
    potentiometerA = VRAMSB;
    potentiometerA = potentiometerA << 8;
    potentiometerA = potentiometerA | VRALSB; 

// IR SENSOR CHALLENGE
// SWB to turn on IR sensor
 
    if(potentiometerA >= 1000 && potentiometerA < 1166)
    { 
        LATCbits.LATC2 = 1; //turn LED on
    }
    else if (potentiometerA >= 1166 && potentiometerA < 1333)
    {
        LATCbits.LATC2 = 0; //turn LED on
    }
    else if (potentiometerA >= 1333 && potentiometerA < 1500)
    {
        LATCbits.LATC2 = 1; //turn LED on
    }
    else if (potentiometerA >= 1500 && potentiometerA < 1667)
    {
        LATCbits.LATC2 = 0; //turn LED on
    }
    else if (potentiometerA >= 1667 && potentiometerA < 1834)
    {

        LATCbits.LATC2 = 1; //turn LED on
    }
    else
    {
        LATCbits.LATC2 = 0; //turn LED on
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
