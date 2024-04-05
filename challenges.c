#include "challenges.h"
#include "data_sorting.h"
#include <xc.h>

int potentiometerA;
uint8_t taskValueLSB = 0x00;
void challenges(){
    
    potentiometerA = VRAMSB;
    potentiometerA = potentiometerA << 8;
    potentiometerA = potentiometerA | VRALSB; 

// IR SENSOR CHALLENGE
// SWB to turn on activate LEDs for challenge
if(switchBMSB == 0x7)
{
    if(potentiometerA >= 1000 && potentiometerA < 1166) //EMITTER 1
    { 
        LATCbits.LATC2 = 1; //turn LED on
                 
        if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X01;
        }
        else
        {
            LATCbits.LATC4 = 0; 
        }
    }
    else if (potentiometerA >= 1166 && potentiometerA < 1333) //EMITTER 2
    {
        LATCbits.LATC2 = 0; //turn LED on
        
        if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X02;
        }
        else
        {
            LATCbits.LATC4 = 0; 
        }
    }
    else if (potentiometerA >= 1333 && potentiometerA < 1500) // EMITTER 3
    {
        LATCbits.LATC2 = 1; //turn LED on
        
        if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X03;
        }
        else
        {
            LATCbits.LATC4 = 0; 
        }
    }
    else if (potentiometerA >= 1500 && potentiometerA < 1667) // EMITTER 4
    {
        LATCbits.LATC2 = 0; //turn LED on
        
        if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X04;
        }
        else
        {
            LATCbits.LATC4 = 0; 
        }
    }
    else if (potentiometerA >= 1667 && potentiometerA < 1834) // EMITTER 5
    {

        LATCbits.LATC2 = 1; //turn LED on
    
            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X05;
        }
        else
        {
            LATCbits.LATC4 = 0; 
        }
    }
    else if (potentiometerA >= 1835 && potentiometerA <= 2000) //EMITTER 6
    {
        LATCbits.LATC2 = 0; //turn LED on
                
        if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC4 = 1; //turn LED on
            taskValueLSB = 0X06;
        }
        else
        {
            LATCbits.LATC4 = 0;
        }
    }
}
    
 
// LASER TURRET DEFENSE CHALLENGE
// SWD to send shield code
if (switchDMSB == 0x7)
{ // if SWD  = 2000, LSB always 0x00

    getPCLS(); // will give shield code flag status

    if (shieldCodeFlag != 0)
    { // A value of !0 means there is a shield code loaded
        
        LATCbits.LATC4 = 1; // green LED on if shield code is transmitting
       
        
        transmitSync(); // sync bytes

        transmitByte(0x02); // MSG ID

        transmitByte(0x09); // MSG ID

        transmitByte(0x01); // Payload LSB

        transmitByte(0x00); // Payload MSB

    }    
    else 
    { 
        LATCbits.LATC4 = 0;
    }
}


    // Switch A used to transmit task value message to processing plant
    if(switchAMSB == 0x7) // if switch A is down, send surface exploration command
    {
        transmitSync();
        
        transmitByte(0x01);
        
        transmitByte(0x0A);
        
        transmitByte(0x04);
        
        transmitByte(0x00);
        
        transmitByte(0x05);
        
        transmitByte(0x00);
        
        transmitByte(taskValueLSB);
        
        transmitByte(00);     
    }
}



