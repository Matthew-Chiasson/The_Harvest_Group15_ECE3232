/*
 * File:   main.c
 * Author: mchiass3
 *
 * Created on February 8, 2024, 6:54 PM
 */
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (EC above 8MHz; PFM set to high power)
#pragma config RSTOSC = HFINT32
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON

#include <xc.h>

#pragma config WDTE = OFF

#define _XTAL_FREQ 32000000

/*
a global variable in place of a parameter to be used by the ISR
*/
int byteToSend;
int noOp = 0;


void setUp(void){
       
    TX1STAbits.TXEN = 1; //Transmit Enable bit: 1 = Transmit enabled
    TX1STAbits.SYNC = 0; //EUSART Mode Select bit: 0 = Asynchronous mode
    
    RC1STAbits.SPEN = 1; // Serial Port Enable bit: 1 = Serial port enabled
    
    BAUD1CONbits.BRG16 = 1; //16-bit Baud Rate Generator bit: 1 = 16-bit Baud Rate Generator is used
                            //0 = 8-bit Baud Rate Generator is used
    
    TX1STAbits.BRGH = 1; //High Baud Rate Select bit: Asynchronous mode: 1= High speed
    
    SP1BRGL = 0b01000000; //Lower eight bits of the Baud Rate Generator
    SP1BRGH = 0b11;       //Upper eight bits of the Baud Rate Generator
    
    INTCONbits.GIE = 1; //Global Interrupt Enable bit: 1 = Enables all active interrupts
    INTCONbits.PEIE = 1; //Peripheral Interrupt Enable bit: 1 = Enables all active peripheral interrupts
    PIE3bits.TXIE = 1; // USART Transmit Interrupt Enable bit: 1 = Enables the USART transmit interrupt
    
    RC5PPS = 0x10; //PPS OUTPUT SIGNAL ROUTING OPTIONS: 0x10 = TX/CK
    
      
}


void __interrupt() _transmitByte(){
    
    
    TX1REGbits.TX1REG = byteToSend;
    
   
}


void transmitByte(int byteToSend_IN){
   
    TX1REG = 0x00; //clear register
    
    byteToSend = byteToSend_IN; //set global var
    _transmitByte(); //ISR
    
}
 

void transmitCommonMotor(void){

    //0xFE1901060400;
    
    transmitByte(0xFE);

    transmitByte(0x19);
    
    transmitByte(0x01);

    transmitByte(0x06);

    transmitByte(0x04);
    
    transmitByte(0x00);

}


void testPulseMotor(int motorA_dir_IN, int motorA_speed_IN, int motorB_dir_IN, int motorB_speed_IN){
    
    transmitCommonMotor();
    
    transmitByte(motorA_dir_IN);
    
    transmitByte(motorA_speed_IN);
        
    transmitByte(motorB_dir_IN);  
    
    transmitByte(motorB_speed_IN);

}

void getPCLS(){

    //recive register has a buffer of 2 bytes
    
    //ask pcls to get data from controller
    
    transmitByte(0xFE); //sink
    
    transmitByte(0x19); //sink
    
    transmitByte(0x01);
    
    transmitByte(0x05);
    
    transmitByte(0x00);
    
    transmitByte(0x00);
    
    //
    

}






void main(void) {
    
    setUp();
    
    //forward on motor A test
    //01 64 00 00
    //0x64 is max speed
    
    while(1){
        
        //testPulseMotor(0x01, 0x64, 0x00, 0xFF);
        //getPCLS();
        
        transmitByte(0x56); //sink
        
        transmitByte(0xFF); //sink
        
        transmitByte(0xF1);
        
        //__delay_ms(2500);
        
        
    } 
    
    return;
}




