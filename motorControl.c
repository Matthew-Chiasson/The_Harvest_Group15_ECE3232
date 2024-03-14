#include "motorControl.h"




void transmitCommonMotor(void){

    //sink has already been called
    transmitByte(0x01);
    transmitByte(0x06);
    transmitByte(0x04);
    transmitByte(0x00);
}



void testPulseMotor(int motorA_dir_IN, int motorA_speed_IN, int motorB_dir_IN, int motorB_speed_IN){
    
    transmitSync();
    transmitCommonMotor();
    
    transmitByte(motorA_dir_IN);
    transmitByte(motorA_speed_IN);   
    transmitByte(motorB_dir_IN);  
    transmitByte(motorB_speed_IN);
}


