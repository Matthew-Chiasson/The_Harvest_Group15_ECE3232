#include "data_sorting.h"

uint8_t messages[100];
uint8_t *messages_origin = messages;
uint8_t *read_here = messages;
uint8_t *receive_here = messages;
uint8_t *end_of_messages = messages+100;
uint8_t data_sorting_error = 0;

uint8_t teamID;
uint8_t playerID;
uint8_t overallHealthLSB;
uint8_t overallHealthMSB;
uint8_t shieldCodeFlag;
uint8_t repairCodeFlag;

uint8_t rightJoyStickXLSB;
uint8_t rightJoyStickXMSB;
uint8_t rightJoyStickYLSB;
uint8_t rightJoyStickYMSB;
uint8_t leftJoyStickYLSB;
uint8_t leftJoyStickYMSB;
uint8_t leftJoyStickXLSB;
uint8_t leftJoyStickXMSB;
uint8_t switchALSB;
uint8_t switchAMSB;
uint8_t switchBLSB;
uint8_t switchBMSB;
uint8_t switchCLSB;
uint8_t switchCMSB;
uint8_t switchDLSB;
uint8_t switchDMSB;
uint8_t VRALSB;
uint8_t VRAMSB;
uint8_t VRBLSB;
uint8_t VRBMSB;

int check()
{
    if(read_here == receive_here)
        return 1;
    return 0;
}


void end(){
    if(read_here == end_of_messages)
        read_here = messages_origin;
    if(receive_here == end_of_messages)
        receive_here = messages_origin;
}
int increase()
{
    read_here ++;
    end();
    if(read_here == receive_here)
        return 1;
    return 0;
}

void get_pcls_info()
{
    uint16_t payload;
    uint8_t searching_error = 10;
    uint8_t search_count = 0;
    
    if(increase())
        return;
    payload = *read_here;
    
    if(increase())
        return;
    payload = payload << 8;
    payload = payload | *read_here;
    
    while(1)
    {
        if ((receive_here > read_here) & (receive_here-read_here >= 7))
            break;
        else if((read_here > receive_here)& (read_here-receive_here <= 93))
            break;
            
        search_count ++;
        if(search_count >= searching_error)
        {
            data_sorting_error = 1;
            return;
        }
    }
    
    if(increase())
        return;
    teamID = *read_here;
    
    if(increase())
        return;
    playerID = *read_here;
    
    if(increase())
        return;
    overallHealthLSB = *read_here;
    
    if(increase())
        return;
    overallHealthMSB = *read_here;
    
    if(increase())
        return;
    shieldCodeFlag = *read_here;
    
    if(increase())
        return;
    repairCodeFlag = *read_here;
}


void get_user_data()
{
    uint16_t payload = *read_here;
    uint8_t searching_error = 10;
    uint8_t search_count = 0;
    
    if(increase())
        return;
    payload = *read_here;
    
    if(increase())
        return;
    payload = payload << 8;
    payload = payload | *read_here;
    
    while(1)
    {
        if ((receive_here > read_here) & (receive_here-read_here >= 21))
            break;
        else if((read_here > receive_here) & (read_here-receive_here <= 79))
            break;
            
        search_count ++;
        if(search_count >= searching_error)
        {
            data_sorting_error = 1;
            return;
        }
    }
    
    if(increase())
        return;
    rightJoyStickXLSB = *read_here;
    if(increase())
        return;
    rightJoyStickXMSB = *read_here;
    
    
    if(increase())
        return;
    rightJoyStickYLSB = *read_here;
    if(increase())
        return;
    rightJoyStickYMSB = *read_here;
    
    
    if(increase())
        return;
    leftJoyStickYLSB = *read_here;
    if(increase())
        return;
    leftJoyStickYMSB = *read_here;
    
    if(increase())
        return;
    leftJoyStickXLSB = *read_here;
    if(increase())
        return;
    leftJoyStickXMSB = *read_here;
    
    
    if(increase())
        return;
    switchALSB = *read_here;
    if(increase())
        return;
    switchAMSB = *read_here;
    
    if(increase())
        return;
    switchBLSB = *read_here;
    if(increase())
        return;
    switchBMSB = *read_here;
    
    if(increase())
        return;
    switchCLSB = *read_here;
    if(increase())
        return;
    switchCMSB = *read_here;
    
    if(increase())
        return;
    switchDLSB = *read_here;
    if(increase())
        return;
    switchDMSB = *read_here;
    
    if(increase())
        return;
    VRALSB = *read_here;
    if(increase())
        return;
    VRAMSB = *read_here;
    
    if(increase())
        return;
    VRBLSB = *read_here;
    if(increase())
        return;
    VRBMSB = *read_here;
}

void sort_data()
{
    uint8_t searching_error = 110;
    uint8_t search_count = 0;
    
    while(*read_here != 0xFE)
    {
        if(check())
            return;
        read_here ++;
        end();
        search_count ++;
        if(search_count >= searching_error)
        {
            data_sorting_error = 1;
            return;
        }
    }
    
    read_here ++;           // sync bit #2
    end();
    if(check())
        return;
    if(*read_here != 0x19)
        return;
    
    read_here ++;           // message LSB
    end();
    if(check())
        return;
    
    read_here ++;           // message MSB
    end();
    if(check())
        return;

    //if (*read_here == 0x04)
        //get_pcls_info();
    //else if(*read_here == 0x05)
    //    get_user_data();
    if(*read_here == 0x05)
        get_user_data();
    
    return;    
}
