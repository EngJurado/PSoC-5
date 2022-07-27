/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
uint16 VALADCx=0;
uint16 VALADCy=0;
uint16 VALADCz=0;
uint16 Theta=0;
uint8 Bandx=0;
uint8 Bandy=0;
uint8 Band45=0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_Start();
    variables_Start();
    LCD_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        variables_Select(0); // Vx
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        VALADCx = ADC_GetResult16();
        variables_Select(1); // Vy
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        VALADCy = ADC_GetResult16();
        variables_Select(2); // Vz
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        VALADCz = ADC_GetResult16();
        LCD_Position(0,0);
        LCD_PrintString("ADCx = ");
        LCD_PrintNumber(VALADCx);
        LCD_Position(1,0);
        LCD_PrintString("ADCy = ");
        LCD_PrintNumber(VALADCy);
        LCD_Position(2,0);
        LCD_PrintString("ADCz = ");
        LCD_PrintNumber(VALADCz);
        CyDelay(500);
        LCD_ClearDisplay();
        if(VALADCx<1492){
            LCD_Position(3,0);
            LCD_PrintString("Theta = ");
            LCD_PrintNumber(0); 
            Bandx=0;
            Bandy=0;
        }       
        if(VALADCx>1485 && VALADCx<=1985 && VALADCz>1710){
            Bandx=1;
            Bandy=0;
            Band45=0;
        }
        if (VALADCz>=1655 && VALADCz<=1710 && VALADCx>1985){
            Band45=1;
            Bandx=0;
            Bandy=0; 
        } 
        if (VALADCz<1655 && VALADCz>1203 && VALADCx>2008){
            Bandx=0;
            Bandy=1; 
            Band45=0;
        }
        if (Bandx==1){
            Theta = (uint32) ((2*VALADCx)-2983)*250/5739;
            LCD_Position(3,0);
            LCD_PrintString("Theta = ");
            LCD_PrintNumber(Theta);            
        }           
        if (Bandy==1){
            Theta = (uint32) (2231-VALADCz)*500/5651;
            LCD_Position(3,0);
            LCD_PrintString("Theta = ");
            LCD_PrintNumber(Theta);
        }
        if (Band45==1){
            Theta = (uint32) (4081-(2*VALADCz))*25/378;
            LCD_Position(3,0);
            LCD_PrintString("Theta = ");
            LCD_PrintNumber(Theta);
        }
    }
}

/* [] END OF FILE */