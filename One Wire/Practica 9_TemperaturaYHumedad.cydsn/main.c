 #include "project.h"

/**Definiciones, utilizando números mágicos que hacen más fácil la lectura del código, 
por lo que cada una de ellas corresponde a un valor específico **/
#define DATO_ESPERANDO_NUEVO_DATO 0
#define DATO_CORRECTO 1
#define DATO_INCORRECTO 2
#define POSITIVA 0
#define NEGATIVA 1
#define CHECKSUM 1
#define TIMEOUT 2
volatile uint8 cont=0;
volatile uint8 vector[40];
volatile uint8 DatosReady=DATO_ESPERANDO_NUEVO_DATO;

//Variables importantes para las mediciones de temperatura, humedad y Checksum
char SignoTemperatura = 0;
uint8 BandTimer = 0;
uint8 errorCheckSum = 0;
uint8 CheckSumMedido = 0;
uint8 VectorUnosCeros [40];
uint8 status = 0;
uint8 contador_error_checksum = 0;
uint8 CheckSum = 0;
uint16 Humedad = 0;
uint16 Temperatura = 0;
uint16 Contador = 0;

/**Funciones que intervienen en el procesamiento de los datos:
 Iniciar sensor, Capturar datos y convertir valores**/
void IniciarSensor(void);
void ConvertirVector (void);
void CaptureData(void);
uint8 TimeOut(uint16);
uint8 GetCheckSum(void);
uint8 CalcularCheckSum (void);
uint16 GetHumedad(void);
uint16 GetTemperatura(void);

/**Funciones que permiten:
* Mostrar en el LCD el error por timeout o el error por checksum
* Mostrar en el LCD los valores obtenidos para la temperatura, humedad y mostrar el valor el valor de checksum recibido y el propio checksum,
y así visualizar que son iguales
* Cuando hayan 3 errores por Checksum, se reinicia el sistema
**/
void MostrarError(char); 
void MostrarVariables (void);
void ReiniciarVariables(void);

//Interrupciones
CY_ISR_PROTO(Counter);
CY_ISR_PROTO(Input_ISR);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    // Inicialización de las interupciones
    isr_counter_StartEx(Counter);
    isr_timer_StartEx(Input_ISR);

    Contador_1_Start(); // Inicialización del contador perteneciente a la función TimeOut, que permite contar tiempos en milisegundos 
    LCD_Start(); // Inicialización del LCD

    for(;;)
    {
        if(TimeOut(2500)){ // Entra aquí cada 2500 milisegundos, la función TimeOut se utiliza para el tiempo de muestreo                        
            IniciarSensor();
            Timer_Start();
            CaptureData();                              
            LED_Write(~LED_Read()); // LED que está aprendiendo y apagando para que muestre que hay comunicación             
            
            /*La bandera DatosReady es una máquina de estados que indica si estamos esperando un nuevo dato, si ya el dato se recibió o 
             si el dato recibido es incorrecto*/
            if(DatosReady==DATO_CORRECTO){ // Si el dato es correcto se convierte el vector de CerosUnos, que es binario, a un decimal, y se obtienen las medidas
                ConvertirVector();                      
                Humedad=GetHumedad();                   
                CheckSum=GetCheckSum();                 
                Temperatura=GetTemperatura();           
                CheckSumMedido=CalcularCheckSum();      
                DatosReady=DATO_ESPERANDO_NUEVO_DATO;   
                
                if(CheckSum != CheckSumMedido){ // Si el Checkssum recibido es diferente al propio, se muestra en el LCD error por Checksum   
                    MostrarError(CHECKSUM);             
                    contador_error_checksum++;
                    if (contador_error_checksum == 3){ // Si hay 3 errores de Checksum se reinicia el sistema
                        contador_error_checksum = 0;
                        CySoftwareReset(); // Es recomendable usarlo en caso de que al haber error por Checksum, el sensor tiene problemas  
                                         // para enviar nuevamente los valores de Checksum correctos, es decir el calculado y medido sean iguales
                    }
                }
                
                else{                                   
                    MostrarVariables();                 
                }
            }
            /** Si la máquina de estados indica que el dato es incorrecto, se muestra en el LCD que hubo un error por TimeOut, es decir, no se
            logró capturar el dato, y se cambia el estado de la bandera DatosReady a esperando nuevo dato**/
            else if(DatosReady==DATO_INCORRECTO){         
                MostrarError(TIMEOUT);                   
                MostrarVariables();                     
                DatosReady=DATO_ESPERANDO_NUEVO_DATO;
                ReiniciarVariables();
            }

        }
        if(errorCheckSum==1){
            errorCheckSum=0;
            MostrarError(CHECKSUM);
            CyDelay(500);
            MostrarVariables();
            CySoftwareReset(); // Genera un reset en el microcontrolador, y se vuelva a hacer la comunicación con el sensor
        }
    }
}

/**Es una función que no retorna nada, sino que se inicia el sensor para que empiece a enviar los datos. Se le envía el pulso inicial con una
duración de 10 ms, y luego se pone el pulso en alto durante 10 us**/
void IniciarSensor(void){   
    cont=0;                 
    DATA_Write(0);
    CyDelay(10);
    DATA_Write(1);
    CyDelayUs(10);
}

/** Ls función TimeOut se utiliza para contar tiempo en milisegundos, y recibe el argumento time que corresponde al número de ms a esperar.
Retorna siempre cero excepto cuando el contador de ms es igual a la cantidad de ms que se le puso como argumento para esperar**/
uint8 TimeOut(uint16 time){
    if(BandTimer){ 
        BandTimer=0;
        Contador++;
        if(Contador==time){     
            Contador=0;         
            return 1;
            }
        else return 0;          
    }
    else return 0;
    }

/** Mientras se están capturando los datos, el sistema no hace nada más. Hay dos formas de salir de ese ciclo repetitivo:
* Haya un TimeOut de 50ms, es decir, hay un dato incorrecto
* Cuando el dato recibido es  correcto**/
void CaptureData(void){
    while(DatosReady==DATO_ESPERANDO_NUEVO_DATO){   
        if(TimeOut(50)){                            
            DatosReady=DATO_INCORRECTO;             
            Timer_Stop();                        
        }                                           
    }
}

//Los valores se converten a 0 y 1
/** En el data entregado por el sensor, los primeros 16 bits corresponden a la humedad, los siguientes 16 bits a la temperatura y los últimos 8 bits al checksum, entonces
se recorre el vector de acuerdo a las posiciones donde se contiene la información de cada variable**/
void ConvertirVector (void){
    for(uint8 i=0; i<40; i++){                                          
        if(vector[i]>65 && vector[i]<95) VectorUnosCeros[i]=0; // Rango del numero de conteos para enviar un cero        
        else if(vector[i]>105 && vector[i]<140) VectorUnosCeros[i]=1;   // Rango del numero de conteos para enviar un uno
    }
}

//Decodifica el valor de humedad
uint16 GetHumedad(void){
    uint16 H=0;
    for(uint8 i=0; i<16; i++){              
        if(VectorUnosCeros[i]==0) H=H<<1;   // Corrimiento hacia la izquierda
        else if(VectorUnosCeros[i]==1){     
            H=H<<1;    //Corrimiento hacia la izquierda y después se suma uno                     
            H++;                            
        }
    }
    return H;
}

//Decodifica el valor de la temperatura
uint16 GetTemperatura(void){                
    uint16 T=0;                             
    for(uint8 i =0;i<16;i++){
        if(VectorUnosCeros[i+16]==0) T=T<<1;
        else if(VectorUnosCeros[i+16]==1){
            T=T<<1;
            T++;
        }
    }
                                            
    T=T&0x7FFF;  // Operación AND (multiplicación). Se asegura que el primer bit sea un cero                           
                                            
    //Se vuelve a tener en cuenta el signo de la temperatura mediante la bandera Signo Temperatura                                        
    if(VectorUnosCeros[16]==0)SignoTemperatura=POSITIVA;    
    else SignoTemperatura=NEGATIVA;         
    return T;                               
}

//Decodifica el CheckSum del sensor
uint8 GetCheckSum(void){
    uint8 CS=0;                                     
    for(uint8 i =0; i<8; i++){                      
        if(VectorUnosCeros[i+32]==0) CS=CS<<1;      
        else if(VectorUnosCeros[i+32]==1){
            CS=CS<<1;
            CS++;
        }
    }
    return CS;
}

//Calcular el CheckSum propio
uint8 CalcularCheckSum (void){                      
    uint8 Chks=0;                                   
    Chks=(uint8)(Humedad>>8)+(uint8)(Humedad)+(uint8)(Temperatura>>8)+(uint8)(Temperatura);
    if(SignoTemperatura==NEGATIVA)Chks+=128;
    return Chks;
}

//Muestra el error de CheckSum o de TimeOut
void MostrarError(char BandError){
    LCD_ClearDisplay();
    if (BandError == 1){
        LCD_Position(2,2);
        LCD_PrintString("Error por CHECKSUM");
    }
    else{
        LCD_Position(2,2);
        LCD_PrintString("Error por TIMEOUT");
    }
    CyDelay(500);
}

//Muestra los resultados en el LCD, la temperatura y humedad con un decimal
void MostrarVariables (void){
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Cks = ");
    LCD_PrintNumber(CheckSum);
    LCD_Position(0,10);
    LCD_PrintString("CksM = ");
    LCD_PrintNumber(CheckSumMedido);
    LCD_Position(2,0);
    LCD_PrintString("Temp = ");
    LCD_PrintNumber(Temperatura/10);
    LCD_PutChar(',');
    LCD_PrintNumber(Temperatura%10);
    LCD_PutChar(LCD_CUSTOM_0);
    LCD_PutChar('C');
    LCD_Position(3,0);
    LCD_PrintString("Humedad = ");
    LCD_PrintNumber(Humedad/10); 
    LCD_PutChar(',');
    LCD_PrintNumber(Humedad%10);
    LCD_PutChar('%');
}

//Reinicia todas las variables usadas
void ReiniciarVariables(void){
    BandTimer = 0;
    errorCheckSum = 0;
    Contador = 0;
    Temperatura = 0;
    CheckSum = 0;
    status = 0;
    Humedad = 0;
    CheckSumMedido = 0;  
}

//Interrupcion del contador, se activa la bandera cada milisegundo
CY_ISR(Counter){ 
    BandTimer=1;                                        
}


CY_ISR(Input_ISR){
    status=Timer_ReadStatusRegister();
    if(status & Timer_STATUS_CAPTURE){   // Entra cada flanco de bajada               
        cont++; // Se lee el valor del flanco de bajada, los 2 primeros no interesan porque son para inicar el sensor
        /** Cuando contador sea de 3 se calculan los conteos hasta el flanco de bajada y se almacenan en el vector de 40 posiciones**/
        if(cont<3){ // Se lee el timer y se vuelve a inicar, es decir, se pone en 65535
            Timer_ReadCapture();                        
            Timer_WriteCounter(65535);                  
        }
        else{             // el contador vale 3                              
            vector[cont-3]=65535-Timer_ReadCapture();  // se halla el número de conteos  
            Timer_WriteCounter(65535);                  
            if(cont>=42){      
               /**  Cuando el contador sea 42, el vector se llena y se activa la bandera DATO_CORRECTO. 
                Se detiene el timer**/
                cont=0;                                 
                Timer_Stop();                           
                DatosReady=DATO_CORRECTO;
            }
        }
    }
}
