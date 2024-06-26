#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINT32
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON

#include <xc.h>
#include <stdbool.h>
#include "motorControl.h"
#include "data_sorting.h"
#include "challenges.h"

#pragma config WDTE = OFF

#define _XTAL_FREQ 32000000


/*
a global variable in place of a parameter to be used by the ISR
*/
int byteToSend = 1;
//int dataIn[208]; // in data_sorting.h now called messages[100]
int payloadSize = 0;
int index = 0;
bool ReceiveComplete;
int here = 0;

void waitForIt(){
    
    while(1){
        if(TX1STAbits.TRMT == 1)
            break;
    }

//boom
}

void setUp(void){
    
    RC5PPS = 0x10; //PPS OUTPUT SIGNAL ROUTING OPTIONS: 0x10 = TX/CK
    RXPPS = 0x16; // PPS INPUT SIGNAL ROUTING: 0x16 = RC6
    
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC5 = 1;
    TX1STAbits.TXEN = 1; //Transmit Enable bit: 1 = Transmit enabled
    TX1STAbits.SYNC = 0; //EUSART Mode Select bit: 0 = Asynchronous mode
    
    RC1STAbits.SPEN = 1; // Serial Port Enable bit: 1 = Serial port enabled
    RC1STAbits.CREN = 1;
    
    BAUD1CONbits.BRG16 = 1; //16-bit Baud Rate Generator bit: 1 = 16-bit Baud Rate Generator is used
                            //0 = 8-bit Baud Rate Generator is used
    
    TX1STAbits.BRGH = 1; //High Baud Rate Select bit: Asynchronous mode: 1= High speed
    SP1BRGL = 0x44; //Lower eight bits of the Baud Rate Generator
    SP1BRGH = 0x00;       //Upper eight bits of the Baud Rate Generator
    //baud rate = 115200
    
    INTCONbits.GIE = 1; //Global Interrupt Enable bit: 1 = Enables all active interrupts
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable bit: 1 = Enables all active peripheral interrupts
    PIE3bits.RCIE = 1;   // Receive interrupt enabled
    ANSELCbits.ANSC6 = 0; // RC6 is digital input
    
    TRISBbits.TRISB1 = 1; //RB1 input
    TRISCbits.TRISC2 = 0; //RC2 output
    ANSELBbits.ANSB1 = 0; //RB1 is digital input
}


void __interrupt() _ISR(){  
    
    if(PIR3bits.TXIF == 1){ //transmit flag
        PIE3bits.TXIE = 0;
        waitForIt();//boom
    }

    
   if(PIR3bits.RCIF == 1){ //receive flag
       
       *receive_here = RC1REG;
        receive_here ++;
        end();
       
    }
}
        

void transmitByte(int byteToSend_IN){
    
    byteToSend = byteToSend_IN; //set global var
    TX1REGbits.TX1REG = byteToSend; //set the register to hold the value
    PIE3bits.TXIE = 1; // USART Transmit Interrupt Enable bit: 1 = Enables the USART transmit interrupt
}
 

void transmitSync(){   
    transmitByte(0xFE); // sync
    transmitByte(0x19); // sync
}
 

void getPCLS(){

    //recive register has a buffer of 2 bytes
    //ask pcls to get data from controller
    
    transmitSync();
    
    transmitByte(0x01); // MSG ID
    transmitByte(0x04); // MSG ID
    transmitByte(0x00);
    transmitByte(0x00);
}

void getUserData(){
    //ask pcls to get data from the RF controller
    
    transmitSync();
    
    transmitByte(0x01); // MSG ID
    transmitByte(0x05); // MSG ID
    transmitByte(0x00);
    transmitByte(0x00);
}

void shoot(){
    
    transmitSync();
    transmitByte(0x01);
    transmitByte(0x09);
    transmitByte(0x01);
    transmitByte(0x00);
    transmitByte(0x01);
    __delay_ms(2);
    
}

void requestHealShot(){

    transmitSync();
    transmitByte(0x03);
    transmitByte(0x09);
    transmitByte(0x00);
    transmitByte(0x00);
    __delay_ms(2);
    
}

void transmitHealShot(){

    transmitSync();
    transmitByte(0x04);
    transmitByte(0x09);
    transmitByte(0x01);
    transmitByte(0x00);
    __delay_ms(2);
    
}

int chaimber = 0;

void handleShooting(){

    if(switchBMSB != 0x3)
        return;
    
    if(switchCMSB == 0x5)
        chaimber = 0;
    
    
    if(switchCMSB == 0x7)
        requestHealShot();
    
    
    //if(switchAMSB == 0x3 && switchCMSB == 0x3)
        //transmitHealShot();
    
        
    if(switchCMSB == 0x3 && switchAMSB == 0x7 && chaimber == 0){ //Ad Bu Cu
        shoot();
        chaimber = 1;
    }
    
}


void main(void) {
    
    setUp();
    
    while(1){
        waitForIt(); //wait for Shift REG
        
        getUserData();
        __delay_ms(2);
        
        sort_data();       
        __delay_ms(2);
        
        motorControl();
        __delay_ms(2);
        
        challenges();
        __delay_ms(2);
        
        handleShooting();
        __delay_ms(2);
         
    } 

    return;
}
