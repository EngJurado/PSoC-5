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

struct Pulso{ //datos del pulso
    uint8 dato1; //dato 1 del promedio movil
    uint8 dato2; //dato 2 del promedio movil
    uint8 dato3; //dato 3 del promedio movil
    uint8 dato4; //dato 4 del promedio movil
    uint8 dato5; //dato 5 del promedio movil
    uint8 datoActual; //dato actual
    uint8 promedioMovil; //promedio movil
    uint8 bandera; // bandera de la interrupcion del comparador
    uint8 dedo; // bandera de si el dedo esta puesto
};

struct Pulso pulso; // se crea la variable pulso que es una estructura

struct Tiempo{ //datos del tiempo
    uint16 ms; // milisegundo
    uint8 ms10; // 10 milisegundos
    uint8 ms100; // 100 milisegundos
};

struct Tiempo tiempo;  // se crea la variable tiempo que es una estructura

struct Voltaje{ // valores que hacen referencia al adc
    uint16 ADC; //valadc
    uint16 mv; //milivoltios
    uint16 dato1; //dato 1 del promedio movil
    uint16 dato2; //dato 2 del promedio movil
    uint16 dato3; //dato 3 del promedio movil
    uint16 dato4; //dato 4 del promedio movil
    uint16 dato5; //dato 5 del promedio movil
    uint16 promedioMovil; //promedio movil
};

struct Voltaje voltaje;  // se crea la variable voltio que es una estructura

CY_ISR_PROTO(Serial); //interrupciones
CY_ISR_PROTO(Ms);
CY_ISR_PROTO(Medicion);
    
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    //inicializar todo
    Opamp_1_Start();
    Opamp_2_Start();
    PGA_Start();
    Comp_Start();
    ADC_Start();
    UART_Start();
    Contador_Start();
    LCD_Start();
    
    //poner las funciones con su interrupcion
    RXInterrupt_StartEx(Serial);
    Temporizador_StartEx(Ms);
    PulsoSensor_StartEx(Medicion);

    for(;;)
    {
        // cada 10 miliseundos se activa una bandera
        if (tiempo.ms%10==0){
            tiempo.ms10 = 1;
        }
        
        //entra aca cada 10 milisegundos
        if(tiempo.ms10){
            tiempo.ms10 = 0;
            tiempo.ms100++;
            //activa una bandera cada 100 milisegundos
            if (tiempo.ms100==11){
                tiempo.ms100 = 1;
            }
            // lee el adc
            ADC_StartConvert();
            ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
            voltaje.ADC = ADC_GetResult16();
            voltaje.mv = (uint32)(5000*voltaje.ADC)/4095; // lo pasa a milivoltios
            
            //lo manda al uart
            UART_PutChar(((voltaje.mv/1000)%10)+48);  
            UART_PutChar(((voltaje.mv/100)%10)+48); 
            UART_PutChar(((voltaje.mv/10)%10)+48); 
            UART_PutChar((voltaje.mv%10)+48); 
            UART_PutCRLF(' ');
                   
            //entra aqui cada que se activa la interrupcion del comparador
            if (pulso.bandera){
                pulso.bandera = 0;
                pulso.datoActual = (uint16) 60000/tiempo.ms; //transforma el dato en frecuencia
                tiempo.ms = 0;
                
                //almacena 5 datos
                pulso.dato5 = pulso.dato4;
                pulso.dato4 = pulso.dato3;
                pulso.dato3 = pulso.dato2;
                pulso.dato2 = pulso.dato1;
                pulso.dato1 = pulso.datoActual;
                
                //cuando todo esta almacenado saca el promedio movil                
                if((pulso.dato1!=0)&&(pulso.dato2!=0)&&(pulso.dato3!=0)&&(pulso.dato4!=0)&&(pulso.dato5!=0)){
                    pulso.promedioMovil=(pulso.dato1+pulso.dato2+pulso.dato3+pulso.dato4+pulso.dato5)/5;
                    pulso.dedo = 1;
                }
            }
            
            //entra cada 100 milisegundos para ver si se quito el dedo y para actualizar el LCD
            if (tiempo.ms100 == 10){
                
                //promedio movil para saber si se quito el dedo
                voltaje.dato5 = voltaje.dato4;
                voltaje.dato4 = voltaje.dato3;
                voltaje.dato3 = voltaje.dato2; 
                voltaje.dato2 = voltaje.dato1;
                voltaje.dato1 = voltaje.mv;
                voltaje.promedioMovil=(voltaje.dato1+voltaje.dato2+voltaje.dato3+voltaje.dato4+voltaje.dato5)/5;
                if (voltaje.promedioMovil>=2100){
                    pulso.dedo = 0;
                }
                
                //si el dedo esta puesto se visualizan los datos
                if (pulso.dedo){
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("F.cardiaca: ");
                    LCD_PrintNumber(pulso.promedioMovil);
                    LCD_PrintString(" LPM");
                    LCD_Position(1,0);
                    LCD_PrintString("F.senal: ");
                    LCD_PrintNumber(pulso.promedioMovil/60);
                    LCD_PutChar('.');
                    LCD_PrintNumber((10*pulso.promedioMovil/60)%10);
                    LCD_PrintString(" HZ");
                }
                
                // si se quito el dedo muetra todo 0 y que no hay dedo
                else{
                    LCD_ClearDisplay();
                    LCD_Position(0,0);
                    LCD_PrintString("F.cardiaca: 0 LPM");
                    LCD_Position(1,0);
                    LCD_PrintString("F.senal: 0 HZ");
                    LCD_Position(2,0);
                    LCD_PrintString("No hay dedo");
                    pulso.dato1 = 0;
                    pulso.dato2 = 0;
                    pulso.dato3 = 0;
                    pulso.dato4 = 0;
                    pulso.dato5 = 0;
                }
            }
        }  
    }
    
}

CY_ISR(Ms){ //cuenta milisegundos
    
    tiempo.ms++;
    
}

CY_ISR(Medicion){ // se activa cada que el comparador funciona
    
    pulso.bandera = 1;
    
}

CY_ISR(Serial){ // no hace nada pero es parte del uart
    
}