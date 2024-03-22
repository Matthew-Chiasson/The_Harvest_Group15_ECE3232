/* 
 * File:   motorControl.h
 * Author: mchiass3
 *
 * Created on March 14, 2024, 7:44 PM
 */

#ifndef MOTORCONTROL_H
#define	MOTORCONTROL_H

extern rightJoyY;
    void transmitCommonMotor(void);
    void testPulseMotor(int motorA_dir_IN, int motorA_speed_IN, int motorB_dir_IN, int motorB_speed_IN);
    void motorControl();
    void transmitByte(int byteToSend_IN); // Add this prototype
    void transmitSync(void); // Add this prototype

#endif	/* MOTORCONTROL_H */
