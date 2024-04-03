
#include "motorControl.h"
#include "data_sorting.h"
#include <math.h>

int rightJoyY;
int rightJoyX;
int power;
float normalX;
float normalY;

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
    
    //left right
    float left_Multiplyer;
    float right_Multiplyer;
     
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
    normalX = (rightJoyX - 1000) / 1000.0;
    normalY = (rightJoyY - 1000) / 1000.0;
    
    normalX = fabs(0.5 - normalX);
    
    //left right
    left_Multiplyer = 1.0;
    right_Multiplyer = 1.0;
    
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
    
    power = 51 + (fabs(0.5 - normalY) * 100);
    
    motorA_speed = power * left_Multiplyer;
    motorB_speed = power * right_Multiplyer;
    
    //tank turn
    
    if(motorA_speed < 55){
        
        motorA_speed = 55 + (55 - motorA_speed);

        //flip dir
        if(motorA_dir == 1)
            motorA_dir = 2;
        
        if(motorA_dir == 2)
            motorA_dir = 1;
        
    }
    
    if(motorB_speed < 55){
        
        motorB_speed = 55 + (55 - motorB_speed);

        //flip dir
        if(motorB_dir == 1)
            motorB_dir = 2;
        
        if(motorB_dir == 2)
            motorB_dir = 1;
        
    }
    
    testPulseMotor(motorA_dir, motorA_speed, motorB_dir, motorB_speed);    
}

