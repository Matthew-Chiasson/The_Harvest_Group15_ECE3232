#include "motorControl.h"
#include "data_sorting.h"
#include <math.h>

int rightJoyY;
int rightJoyX;

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
    
    /*
    transmitByte(motorB_dir_IN);
    transmitByte(motorA_speed_IN);   
    transmitByte(motorA_dir_IN);  
    transmitByte(motorB_speed_IN);
    */
    
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
    
    int deadzone = 10;
     
    //forward backward
    rightJoyY = rightJoyStickYMSB;
    rightJoyY = rightJoyY << 8;
    rightJoyY = rightJoyY | rightJoyStickYLSB;
    
    //left right
    rightJoyX = rightJoyStickXMSB;
    rightJoyX = rightJoyX << 8;
    rightJoyX = rightJoyX | rightJoyStickXLSB;
    
    //forward backward
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
    
    
    //turns the value of the joystick into a 0 - 1.0 value
    int normalX = (rightJoyX - 1000) / 1000;
    int normalY = (rightJoyY - 1000) / 1000;
    
    normalX = abs(0.5 - normalX);
    
    //left right
    float left_Multiplyer = 1.0;
    float right_Multiplyer = 1.0;
    
    
    int power;
    
    
    if(rightJoyX > 1500 + deadzone){
        
        left_Multiplyer = 1.0 + normalX;
        right_Multiplyer = 1.0 - normalX;
    
    }else if(rightJoyX < 1500 - deadzone){
        
        left_Multiplyer = 1.0 - normalX;
        right_Multiplyer = 1.0 + normalX;
        
    }else{
    
        left_Multiplyer = 1.0;
        right_Multiplyer = 1.0;
        
    }
    
    power = 51 + (abs(0.5 - normalY) * 100);
    
    motorA_speed = power * left_Multiplyer;
    motorB_speed = power * right_Multiplyer;
    
    if(motorA_speed < 51){
        motorA_speed = 55;
    }
    
    if(motorB_speed < 51){
        motorB_speed = 55;
    }
    
    
    testPulseMotor(motorA_dir, motorA_speed, motorB_dir, motorB_speed);    
}
