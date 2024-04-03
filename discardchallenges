
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
    if(switchBMSB == 0x20) // 2000 means switch up, LSB always 00
    {
            TRISBbits.TRISB1 = 1; //RB1 input
            TRISCbits.TRISC2 = 0; //RC2 output
            ANSELBbits.ANSB1 = 0; //RB1 is digital input
            
            // Let RC4, RC3, and RB5 be LED0, LED1, and LED2 respectively
         //   TRISCbits.TRISC4 = 0; // LED output pins
         //   TRISCbits.TRISC3 = 0; 
          //  TRISBbits.TRISB5 = 0; 
            
    
    if      (potentiometerA>=1000 && potentiometerA<1166)
    { 
      //  LATCbits.LATC4 = 1;
     //   LATCbits.LATC3 = 0;
     //   LATBbits.LATB5 = 0;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    
    }
    else if (potentiometerA>=1166 && potentiometerA<1333)
    {
   //     LATCbits.LATC4 = 0;
     //   LATCbits.LATC3 = 1;
      //  LATBbits.LATB5 = 0;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    }
    else if (potentiometerA>=1333 && potentiometerA<1500)
    {
     //   LATCbits.LATC4 = 1;
     //   LATCbits.LATC3 = 1;
      //  LATBbits.LATB5 = 0;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    }
    else if (potentiometerA>=1500 && potentiometerA<1667)
    {
    //    LATCbits.LATC4 = 0;
    //    LATCbits.LATC3 = 0;
    //    LATBbits.LATB5 = 1;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    }
    else if (potentiometerA>=1667 && potentiometerA<1834)
    {
     //   LATCbits.LATC4 = 1;
     //   LATCbits.LATC3 = 0;
     //   LATBbits.LATB5 = 1;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    }
    else if (potentiometerA<=1834 && potentiometerA<2000)
    {
     //   LATCbits.LATC4 = 0;
     //   LATCbits.LATC3 = 1;
     //   LATBbits.LATB5 = 1;

            if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
        }
    }
         
    if (PORTBbits.RB1 == 0) //While IR sensor is active
        {
            LATCbits.LATC2 = 1; //turn LED on
        }
    else
       {
            LATCbits.LATC2 = 0; // necessary?
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
