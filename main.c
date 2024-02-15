/*
 * File:   main.c
 * Author: mchiass3
 *
 * Created on February 8, 2024, 6:54 PM
 */


#include <xc.h>
#pragma config RSTOSC = HFINT32
#pragma config WDTE = OFF


/*
a global variable in place of a parameter to be used by the ISR
*/
int byteToSend;



void setUp(void){
       
    TX1STAbits.TXEN = 1;
    TX1STAbits.SYNC = 0;
    
    RC1STAbits.SPEN = 1;
    
    BAUD1CONbits.BRG16 = 1;
    
    TX1STAbits.BRGH = 1;
    
    SP1BRGL = 0b01000000;
    SP1BRGH = 0b11;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE3bits.TXIE = 1;
    
    RC5PPS = 0x10;
      
}


void __interrupt() _transmitByte(){

    TX1REGbits.TX1REG = byteToSend; 
   
}

void transmitByte(int byteToSend_IN){
    
    byteToSend = byteToSend_IN;
    _transmitByte(); //ISR
    
}


void setByte(int byte_IN){ //not currently in use but would be helpful to implement for cleaner code

    byteToSend = byte_IN;

}
 

void transmitCommonMotor(void){

    //0xFE1901060400;
//    byteToSend = 0xFE;
//    _transmitByte();
    transmitByte(0xFE);
    
//    byteToSend = 0x19;
//    _transmitByte();
    transmitByte(0x19);
    
//    byteToSend = 0x01;
//    _transmitByte();
    transmitByte(0x01);
    
//    byteToSend = 0x06;
//    _transmitByte();
    transmitByte(0x06);
    
//    byteToSend = 0x04;
//    _transmitByte();
    transmitByte(0x04);
    
//    byteToSend = 0x00;
//    _transmitByte();
    transmitByte(0x00);

}


void testPulseMotor(int motorA_dir_IN, int motorA_speed_IN, int motorB_dir_IN, int motorB_speed_IN){
    
    //TX1STAbits.TXEN = 1;
    
    transmitCommonMotor();
    
    //byteToSend = motorA_dir_IN;
    //_transmitByte();
    transmitByte(motorA_dir_IN);
    
    //byteToSend = motorA_speed_IN;
    //_transmitByte();
    transmitByte(motorA_speed_IN);
    
    
    //byteToSend = motorB_dir_IN;
    //_transmitByte();
    transmitByte(motorB_dir_IN);
    
    //byteToSend = motorB_speed_IN;
    //_transmitByte();
    transmitByte(motorB_speed_IN);

}

void main(void) {
    
    setUp();
    
    //forward on motor A test
    //01 64 00 00
    //0x64 is max speed
    
    while(1){
        
        testPulseMotor(0x01, 0x64, 0x00, 0xFF);
        
    } 
    
    return;
}





