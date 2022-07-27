


/* PRÁCTICA 2 - SENSORES Y ACONDICIONAMIENTO DE SEÑALES

INTEGRANTES
Laura Marcela Berrío Vélez
Carlos Mateo Jurado Díaz
Daniela Medina Castrillón 



*/



//Declaración de funciones y variables

#include "project.h"
CY_ISR_PROTO(Subir); // Declaración de la función que realizará la interrupción en la subida de los pasajeros
CY_ISR_PROTO(Bajar); // Declaración de la función que realizará la interrupción en la bajada de los pasajeros
CY_ISR_PROTO(ISR_15S); // 
uint8 timer = 0; // Bandera que se activa cuando la función de interrpción del tiempo se está ejecutando 
uint8 timer2 = 0; // Bandera que activa cuando hay una interrupcion del contador, y la bandera timer es igual a 1
uint16 cont = 0; // Variable con la cual se controlará el tiempo en el que deben ser activados los dos sensores, puesto que en menos de 1.5 s, sube o baja un pasajero
uint8 subiendo = 0; // Bandera que se activa, decir vale 1,  en caso de que la función ”Subir“ se esté ejecutando
uint8 bajando = 0; // Bandera que se activa, es decir, vale 1, en caso de que la función ”bajar“ se esté ejecutando
uint8 pasajeros=0; // Variable que permite saber cual es la cantidad de pasajeros en el bus


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_1_StartEx(Subir); //Inicialización de la interrupción para el conteo de subida
    isr_2_StartEx(Bajar); //Inicialización de la interrupción para el conteo de bajada
    isr_timer_StartEx(ISR_15S); // Se incializa la función de interrupción
    LCD_Start(); // Se inicializa la pantalla LCD
    Counter_Start(); // Inicialización de contador 
    LCD_Position(0,0); // 
    LCD_PrintString("Pasajeros: "); // Se imprime "Pasajeros" en la pantalla LCD en la posición indicada
    LCD_Position(0,11);
    LCD_PrintNumber(pasajeros); // Permite mostrar en la Pantalla la cantidad de pasajeros actual
    LED_Write(0); // EL LED inicialmente está apagado
    
    for(;;)
    {

        if(subiendo==1){ // Se activa la función ”Subir“ cuando la bandera subiendo vale 1, y se incrementa en uno el número de pasajeros
            subiendo=0; // Una vez realizado el conteo de que se subió un pasajero, nuevamente la bandera toma un valor de cero, para así poder identificar posteriormente si un nuevo pasajero se sube o baja del bus
            pasajeros++; // Contador de pasajeros, cuando un pasajero se sube al bus se incrementa en 1 la cantidad cada vez que se ejecuta la función subir
            if(pasajeros<11)LED_Write(0);// El LED permanece apagado siempre y cuando la cantidad de pasajeros no sobrepase a 10
            else LED_Write(1);// A partir de 11 pasajeros se enciende el LED
            LCD_Position(0,11); // Posición en la que se muestra el número de pasajeros actual 
            LCD_PrintNumber(pasajeros);
            isr_1_Disable();// Deshabilita el contador de subida
            isr_2_Disable();//Deshabilita el contador de bajada
            timer=1;   
        }
       
        if(bajando==1){ // Se activa la función ”Bajar“ cuando la bandera bajando vale 1, y se disminuye en uno el número de pasajeros
            bajando=0; // Una vez realizado el conteo de que se bajó un pasajero, nuevamente la bandera toma un valor de cero, para así poder identificar posteriormente si un nuevo pasajero se sube o baja del bus
            pasajeros--; // Decremento de pasajeros, cuando un pasajero se baja del bus disminuye en 1 la cantidad cada vez que se ejecuta la función bajar
            if(pasajeros<10){ // Si el número de pasajeros es menor a 10 el LED permanece apagado 
                LED_Write(0);
                LCD_ClearDisplay(); // Se limpia la información mostrada en el LCD y  a continuación se muestra en la pantalla la cantidad actual de pasajeros
                LCD_Position(0,0);
                LCD_PrintString("Pasajeros: ");  // Se muestra en la pantalla LCD el mensaje "Pasajeros:" 
                LCD_Position(0,11); // Al lado del mensaje "Pasajeros:" se muestra la cantidad actual de pasajeros
                LCD_PrintNumber(pasajeros); 
                LCD_Position(3,0); // Posición en la que se muestra el conteo de 0 a 900 (1.5 segundos)
                LCD_PrintNumber(cont); //       
            }
            else LED_Write(1); // Si la ccantidad de pasajeros montados en el bus sobrepasa los 10 pasajeros el LED se enciende
            
            
            if(pasajeros==255){ // En caso de que el bus esté vacío, es decir la cantidad de pasajeros es cero, y se detecta una señal de bajada, el conteo permanece en cero pasajeros 
                LED_Write(0); // LED apagado
                pasajeros=0; 
               }

            LCD_Position(0,11);
            LCD_PrintNumber(pasajeros);
            isr_1_Disable(); // Deshabilita el contador de subida
            isr_2_Disable(); //Deshabilita el contador de bajada
            timer=1;
        }
        if(pasajeros>=11){ // Si el número de pasajeros supera la cantidad de 11, se observa en la pantalla LCD una alerta que dice EXCESO DE PASAJEROS 
            LCD_Position(1,0); // Posición donde se muestra en la pantalla LCD la alerta de EXCESO DE PASAJEROS
            LCD_PrintString("EXCESO DE PASAJEROS");
        }        
       
        if(timer2==1){ // Cuando se ejecuta la función de interrupción de tiempo y se activa la bandera timer, se hace el conteo del tiempo el cual aumenta hasta llegar a 900
            cont++; // Aumenta en de uno el conteo del tiempo
            LCD_Position(3,0);
            LCD_PrintNumber(cont); // Se va mostrando en la pantalla LCD el número de conteos    
            timer2=0; // Se deshabilita la bandera, para así poder realizar un futuro conteo del tiempo
        }
        
        // Contador del tiempo: 900 conteos= 1.5s, termina de contar los 900 y en 901 comienza de nuevo
        if(cont==901){ // Cuando el tiempo es mayor a 1.5 segundos se inicializa el contador y se desactivan las banderas
            cont=0;
            timer=0;
            timer2=0;
            bajando=0;
            subiendo=0;
            LCD_ClearDisplay(); // Se borra el conteo del tiempo mostrado en la pantalla, para así poder dar paso a visualizar un próximo conteo
            LCD_Position(0,0);
            LCD_PrintString("Pasajeros: ");  
            LCD_Position(0,11);
            LCD_PrintNumber(pasajeros); 
            LCD_Position(3,0);
            LCD_PrintNumber(cont);               
            isr_1_ClearPending();// Limpia la interrupción del último conteo de subida
            isr_2_ClearPending();// Limpia la interrupción del último conteo de bajada          
            isr_1_Enable();// Habilita los contadores de subida
            isr_2_Enable();// Habilita los contadores de bajada
        }


        
    }
}
//Función de interrupción encargada de contabilizar el tiempo de activación de los dos sensores 
CY_ISR(ISR_15S){ 
    if (timer == 1 )timer2=1; 
}
// Función interrupción 1 para conteo de subida de pasajeros
CY_ISR(Subir){ 
    subiendo=1; 
    bajando=0;
}
// Función interrupción 1 para conteo de bajada de pasajeros
CY_ISR(Bajar){ 
    bajando=1;
    subiendo=0;
}


/* [] END OF FILE */
