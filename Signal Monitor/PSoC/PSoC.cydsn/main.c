/*
==========================================
    Created on Mon Jan 8 15:09:13 2021

    @author: Carlos Mateo Jurado Díaz
==========================================
*/

#include "project.h"

uint32 datos=0; //Variable where the value of the ADC is stored 

int main(void)
{
    CyGlobalIntEnable; //Global interrupts are initialized 
    
    UART_Start(); //The UART is initialized 
    ADC_Start(); //The ADC is initialized 
    ADC_SetScaledGain(8190); //ADC range is set from 0V to 10V 

    for(;;)
    {
        ADC_StartConvert(); //ADC starts to convert 
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);  //Waiting for results
        datos=ADC_GetResult16();ADC_StartConvert(); //The value read is assigned to the variable datos

        UART_PutChar('b'); //Start flag
        
        UART_PutChar(((datos/1000)%10)+48); //X-.--
        UART_PutChar(((datos/100)%10)+48); //-X.--
        UART_PutChar(((datos/10)%10)+48); //--.X-
        UART_PutChar((datos%10)+48); // --.-X
        
        UART_PutChar('c'); //Stop flag
        
        CyDelay(10); //10ms of waiting
    }
}