#include "motorControl.h"
#include "data_sorting.h"



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

void motorControl()
{
    int motorA_dir;
    int motorB_dir;
    int motorA_speed;
    int motorB_speed;
    transmitSync();
    
    if((rightJoyStickYMSB >= 0x05))
    {
        motorA_dir = 1;
        motorB_dir = 1;
    }
    else
    {
        motorA_dir = 2;
        motorB_dir = 2;
        
    }
    transmitCommonMotor();
    transmitByte(motorA_dir);
    transmitByte(50);   
    transmitByte(motorB_dir);  
    transmitByte(50);
    
}
