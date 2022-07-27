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
CY_ISR_PROTO(ISR_Tarado);//funcion interrupcion
uint8 band_ADC=0;//se activa cuando se cuentan 10 valores de ADC, activa el promedio del ADC (10 muestras)
uint8 ban_boton=0;//se activa con a interrupcion del boton "Tarado"
uint8 cont_ADC=0;//contador de valores de ADC
uint32 Valor;//variable para valores entrantes de ADC
uint64 VADC=0;//variable pormedio de ADC de 10 muestras
uint64 Peso=0;//variable ecuacion de visualizacion
uint32 ReadCount(void);//Funcion modulo HX711
//valores ecuacion de visualizacion
uint64 b=8802541;//intercepto, valor inicial sin peso (0g)
uint64 z=100;
uint64 m=189598;//pendiente 

int main(void)
{
    LCD_Start();//inicializacion LCD
    isr_Tarado_StartEx(ISR_Tarado);//inicializacion interrupcion 
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        cont_ADC++;//contador para muestras de ADC
        if(cont_ADC==9)band_ADC=1;//10 muestras
        Valor= (uint32)(ReadCount());//valor ADC de la funcion ReadCount()
        VADC= (uint64)Valor+VADC;//sumatoria de muestras
        CyDelay(200);//tiempo de toma de muestras
        if(band_ADC==1){
            band_ADC=0;//inicializacion bandera ADC
            cont_ADC=0;//inicislizacion contador ADC
            VADC=VADC/10; //promedio de 10 muestras
            //visualizacion valores de ADC
            LCD_ClearDisplay();
            LCD_Position(0,5);
            LCD_PrintString("BALANZA");             
            LCD_Position(2,0);
            LCD_PrintString("ADC = ");            
            LCD_PrintU32Number(VADC);   
            if(VADC>b){//visualizacion valores de peso positivo
                Peso=(uint64)(VADC-b)*z/m;//Ecuacion de visualizacion en funcion de ADC
                //visualizacion del peso
                LCD_Position(3,0);
                LCD_PrintString("Peso = ");
                LCD_PrintU32Number(Peso);
                LCD_PrintString("g");
             }
            if(VADC<b){//visualizacion valores de peso negativo
                Peso=(uint64)(b-VADC)*z/m;//Ecuacion de visualizacion en funcion de ADC
                if(Peso==0){
                    //visualizacion del peso
                    LCD_Position(3,0);
                    LCD_PrintString("Peso = 0g");                    
                }
                else{
                    //visualizacion del peso negativo
                    LCD_Position(3,0);
                    LCD_PrintString("Peso = -");
                    LCD_PrintU32Number(Peso);
                    LCD_PrintString("g");
                }
            }           
        }
        if(ban_boton){//boton Tarado
            b=Valor;//se iguala al ultimo valor Tarado 
            ban_boton=0;//inicializacion bandera Tarado
        }
     }     
}

CY_ISR(ISR_Tarado){//funcion interrupcion bton Tarado
    ban_boton=1;//bandera boton Trarado 
}
uint32 ReadCount(void){//funcion para datos ADC entregados de HX711
    uint32 count;//variable para valor ADC
    ADDO_Write(1);//pin recepcion de dato ADC, inicialmente en alto
    ADSK_Write(0);//pin de pulso en bajo
    count=0;//inicializacion de variable
    while (ADDO_Read()){}
    for(uint8 i=0; i<24; i++){//contador en pulsos para contenido del valor ADC
        ADSK_Write(1);//pin de pulso en alto
        count=count<<1;//desplazamiento del valor anterior hacia la izquierda
        ADSK_Write(0);//pin de pulso en bajo
        if(ADDO_Read())count++;//contador suma cada vez que lee el dato
    }
      ADSK_Write(1);//pin de pulso en alto. inicializacion del siguente valor ADC
      CyDelayUs(1);//retraso de 1us
      count=count^0x800000; //asegurar que el valor del dato sea positivo
      ADSK_Write(0);//pin de pulso en bajo
      return(count);//Retorna el valor ADC
}


/* [] END OF FILE */
