#include "motorControl.h"
#include "data_sorting.h"


int rightJoyY;
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
    
    
    transmitByte(motorB_dir_IN);
    transmitByte(motorA_speed_IN);   
    transmitByte(motorA_dir_IN);  
    transmitByte(motorB_speed_IN);
}

void motorControl()
{
    int motorA_dir;
    int motorB_dir;
    int motorA_speed = 51;
    int motorB_speed = 51;
    //transmitSync();
    
    int deadzone = 20;
    
    rightJoyY = rightJoyStickYMSB;
    rightJoyY = rightJoyY << 8;
    rightJoyY = rightJoyY | rightJoyStickYLSB;
    
    if((rightJoyY > 1500 + deadzone))
    {
        motorA_dir = 1;
        motorB_dir = 1;
    }
    else if(rightJoyY < 1500 - deadzone)
    {
        motorA_dir = 2;
        motorB_dir = 2; 
    }
    else
    {
        motorA_dir = 0;
        motorB_dir = 0; 
    }
    
    
    testPulseMotor(motorA_dir, motorA_speed, motorB_dir, motorB_speed);    
}