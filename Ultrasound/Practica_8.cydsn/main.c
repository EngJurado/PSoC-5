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
CY_ISR_PROTO(Medicion_1);//Interrupcion Boton_1 medicion del sensor al piso-->medicion1
CY_ISR_PROTO(Medicion_2);//Interrupcion Boton_2 medicion del sensor al objeto-->medicion2
CY_ISR_PROTO(ISR_Timer);//Interrupcion Timer
CY_ISR_PROTO(Contador);//Interrupcion contador
void Reinit(void); // Se declara la funcion de reinicio del sistema
uint16 VALADC=0; //valor ADC sensor de temperatura
uint32 Temperatura=0; // variable temperatura
int8 status=1;// estado del timer
int16 Count_M1=0;//contador medicion 1
int16 Count_M2=0;//contador medicion 2
int8 ban_M1=0;//Bandera interrupcion medicion 1
int8 ban_M2=0;//Bandera interrupcion medicion 2
int8 ban_M11=0;//Bandera contador medicion1 
int8 ban_M22=0;//Bandera contador medicion2
int8 ban_trig1=0;//Bandera Trigger PWM para medicion 1
int8 ban_trig2=0;//Bandera Trigger PWM para medicion 2
uint32 Velocidad=0;// variable velocidad de sonido
uint32 Distancia=0;// variable Distancia sensada
uint32 Distancia1=0;// variable Distancia medicion1
uint32 Distancia2=0;// variable Distancia medicion 2
uint32 Distancia3=0;// variable Distancia del objeto
int8 Calculos=1;//Bandera Calculo de mediciones 
uint32 valor1=0;//Valor datos en flanco de subida
uint32 valor2=0;//Valor datos en flanco de bajada
uint32 valor3=0;//Valor siguiente ciclo
uint8 ovf1=0;//Valor desbordamiento del Inputcapture 
uint8 ovf2=0;//Valor desbordamiento del Inputcapture
uint32 CiclosDureza=0;//Valor entre flanco de subida y flanco de bajada 
uint8 cont=0;//contador de registros 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
       
    ADC_Start();//Inicializacion ADC
    LCD_Start();//Inicializacion LCD
    Timer_Start();//Inicializacion Timer
    PWM_Start();//Inicializacion PWM
    Counter_Start();//Inicializacion contador
    Timer_isr_StartEx(ISR_Timer);//Inicializacion funcion interrupcion Timer
    Contador_isr_StartEx(Contador);//Inicializacion funcion interrupcion contador
    Boton1_isr_StartEx(Medicion_1);//Inicializacion funcion interrupcion Boton1
    Boton2_isr_StartEx(Medicion_2);//Inicializacion funcion interrupcion Boton2
    Boton2_isr_Disable();//Boton2 comienza desabilitado
    Opamp_Start();//Inicializacion amplificador   
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */   
        ADC_StartConvert();//Comienza conversion a datos ADC
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);//finaliza conversion a datos ADC
        VALADC = ADC_GetResult16();// Resultado de ADC
        Temperatura=(VALADC*1024/910)-100;//Ecuacion de temperatura (x10--> 1 decimal) basado en el voltaje de 1.024v del PSoC y 10mV/ºC
        if(Calculos)// Entra cada vez que finaliza un ciclo
        {          
            CiclosDureza=(uint32)(ovf1*256)+valor1-valor2; //Distancia en datos entre el flanco de subida y el flanco de bajada 
            Velocidad=(uint32)33160+(6*Temperatura);//Velocidad del sonido (x100)
            Distancia=Velocidad*CiclosDureza/100000;//Ditancia con Frecuencia de Timer = 2* 500000Hz (x1000--> 2 decimales en cm o 4 en m)  
            Calculos=0;//desactiva la bandera de calculos
            Timer_Start();//Reinicia para un proximo registro
            //inicializacion de las variables 
            ovf1=0;
            cont=0;
            valor1=0;
            valor2=0;            
        }
        if (ban_M11){//Bandera activada en la interrupcion del contador
            ban_M11=0;
            Count_M1++;
        }
        if(Count_M1==2)ban_M1=1;// conteos para estabilizacion
        if(ban_M1){
            Pin_Write(0);//Pin trigger en bajo
            PWM_Sleep(); //PWM deja de funcionar 
            Distancia1=Distancia;// Se designa la distancia de la medicion 1
            Reinit();// Funcion de reinicio de los valores 
        }
        if (ban_M22){//Bandera activada en la interrupcion del contador
            ban_M22=0;
            Count_M2++;
        }
        if(Count_M2==2){// conteos para estabilizacion
            ban_trig2=0;
            ban_M2=1;}
        
        if(ban_M2){
            Pin_Write(0);//Pin trigger en bajo
            PWM_Sleep();//PWM deja de funcionar 
            Boton1_isr_Enable();//se desabilita el Boton de medicion 1
            Distancia2=Distancia;// Se designa la distancia de la medicion 2
            if(Distancia1>Distancia2)Distancia3 = Distancia1 - Distancia2;// Medicion 1> Medion 2
            else ban_trig2=1;// si no, se activa la bandera  
            Reinit();// Funcion de reinicio de los valores 
        }         
        //Visualizacion de las altura o distancia de medicion 1
        LCD_Position(0,0);
        LCD_PrintString("A1:");
        LCD_PrintNumber(Distancia1/10000);
        LCD_PutChar('.'); //en m con 4 decimales                  
        LCD_PrintNumber(Distancia1/1000%10);
        LCD_PrintNumber(Distancia1/100%10);
        LCD_PrintNumber(Distancia1/10%10);
        LCD_PrintNumber(Distancia1%10);
        LCD_PrintString("m");
        //Visualizacion de las altura o distancia de medicion 2
        LCD_Position(1,0);
        LCD_PrintString("A2:");
        LCD_PrintNumber(Distancia2/10000);
        LCD_PutChar('.');  //en m con 4 decimales                 
        LCD_PrintNumber(Distancia2/1000%10);
        LCD_PrintNumber(Distancia2/100%10);
        LCD_PrintNumber(Distancia2/10%10);
        LCD_PrintNumber(Distancia2%10);
        LCD_PrintString("m");       
        LCD_Position(2,3);
        //Visualizacion de las altura o distancia del objeto medido
        LCD_PrintString("Altura objeto:");
        LCD_Position(3,2);
        LCD_PrintNumber(Distancia3/100);
        LCD_PutChar('.');//en cm con 2 decimales                   
        LCD_PrintNumber(Distancia3/10%10);
        LCD_PrintNumber(Distancia3%10);
        LCD_PrintString("cm");
        LCD_PutChar('-');
        LCD_PrintNumber(Distancia3/10000);
        LCD_PutChar('.');//en m con 4 decimales               
        LCD_PrintNumber(Distancia3/1000%10);
        LCD_PrintNumber(Distancia3/100%10);
        LCD_PrintNumber(Distancia3/10%10);
        LCD_PrintNumber(Distancia3%10);
        LCD_PrintString("m");
        //Visualizacion de la temperatura 
        LCD_Position(0,13);
        LCD_PrintString("Temp:");
        LCD_Position(1,13);  
        LCD_PrintNumber(Temperatura/10);                  
        LCD_PutChar('.');// en ºc con 1 decimal                  
        LCD_PrintNumber(Temperatura%10);
        LCD_PutChar(0xDF);
        LCD_PutChar('C');
        CyDelay(500);
        LCD_ClearDisplay();       
   }
}
CY_ISR(ISR_Timer){
    
    status=Timer_ReadStatusRegister();//Leer el registro de estado
    if(status & Timer_STATUS_TC) //Entra aquí si la interrupción fue por TC
    {
        if(cont==1 )ovf1++; //Cuenta número de desbordamientos durante tiempo en alto
        if(cont==2 )ovf2++; //Cuenta número de desbordamientos durante tiempo en bajo
    }
    if(status & Timer_STATUS_CAPTURE) //Entra aquí si la interrupción fue captura
    {
        if(cont==0)
        {
            valor1=Timer_ReadCapture(); //Obtiene primer valor
            cont++;
        }
        else if(cont==1)
        {
            valor2=Timer_ReadCapture(); //Obtiene segundo valor
            cont++;
        }
        else if(cont==2 )
        {
            Timer_Stop(); //Detiene el timer
            valor3=Timer_ReadCapture(); //Obtiene tercer valor
            Calculos=1; //Bandera que indica cálculos y visualización
        }
    }
}

CY_ISR(Contador){
    if(ban_trig1)ban_M11=1;//Activacion Bandera contador medicion 1
    if(ban_trig2)ban_M22=1;//Activacion Bandera contador medicion 2
}

CY_ISR(Medicion_1){
    Boton2_isr_Enable();//Se habilita el boton 2
    PWM_Start();//inicializacion de PWM
    Pin_Write(1);//Pin trigger PWM en alto
    ban_trig1=1;//Activacion de contador 
    Distancia1=0;//inicializacion del valor de distancia 
}
CY_ISR(Medicion_2){
    Boton1_isr_Disable();// se deshabilita el boton 1
    PWM_Start();//Inicializacion de PWM
    Pin_Write(1);//Pin trigger PWM en alto
    ban_trig2=1;  //Activacion de contador   
    Distancia2=0;//inicializacion del valor de distancia 
    Distancia3=0;//inicializacion del valor de distancia 
}
void Reinit(){ // Se define la funcion reinicio, la cual permite llevar al estado inicial todas las variables utilizada
    LCD_ClearDisplay();
    status=1;
    Count_M1=0;
    Count_M2=0;
    ban_M1=0;
    ban_M2=0;
    ban_M11=0;
    ban_M22=0;
    Distancia=0;
    ban_trig1=0;
    ban_trig2=0;
    Calculos=1;
    valor1=0;
    valor2=0;
    valor3=0;
    ovf1=0;
    ovf2=0;
    CiclosDureza=0;
    cont=0;   
}
/* [] END OF FILE */
