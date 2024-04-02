/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>


// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

#ifndef DATA_SORTING_H
#define DATA_SORTING_H

extern uint8_t messages[100];
extern uint8_t *messages_origin;
extern uint8_t *read_here;
extern uint8_t *receive_here;
extern uint8_t *end_of_messages;
extern uint8_t data_sorting_error;

extern uint8_t teamID;
extern uint8_t playerID;
extern uint8_t overallHealthLSB;
extern uint8_t overallHealthMSB;
extern uint8_t shieldCodeFlag;
extern uint8_t repairCodeFlag;

extern uint8_t rightJoyStickXLSB;
extern uint8_t rightJoyStickXMSB;
extern uint8_t rightJoyStickYLSB;
extern uint8_t rightJoyStickYMSB;
extern uint8_t leftJoyStickYLSB;
extern uint8_t leftJoyStickYMSB;
extern uint8_t leftJoyStickXLSB;
extern uint8_t leftJoyStickXMSB;
extern uint8_t switchALSB;
extern uint8_t switchAMSB;
extern uint8_t switchBLSB;
extern uint8_t switchBMSB;
extern uint8_t switchCLSB;
extern uint8_t switchCMSB;
extern uint8_t switchDLSB;
extern uint8_t switchDMSB;
extern uint8_t VRALSB;
extern uint8_t VRAMSB;
extern uint8_t VRBLSB;
extern uint8_t VRBMSB;
extern unit8_t TSVMSB;
extern unit8_t TSVLSB;



int check();
void end();
int increase();
void sort_data();
void get_pcls_info();
void get_user_data();

#endif



// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

