/*******************************************************************************
* File Name: Contador_1_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Contador_1.h"

static Contador_1_backupStruct Contador_1_backup;


/*******************************************************************************
* Function Name: Contador_1_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Contador_1_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Contador_1_SaveConfig(void) 
{
    #if (!Contador_1_UsingFixedFunction)

        Contador_1_backup.CounterUdb = Contador_1_ReadCounter();

        #if(!Contador_1_ControlRegRemoved)
            Contador_1_backup.CounterControlRegister = Contador_1_ReadControlRegister();
        #endif /* (!Contador_1_ControlRegRemoved) */

    #endif /* (!Contador_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Contador_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Contador_1_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Contador_1_RestoreConfig(void) 
{      
    #if (!Contador_1_UsingFixedFunction)

       Contador_1_WriteCounter(Contador_1_backup.CounterUdb);

        #if(!Contador_1_ControlRegRemoved)
            Contador_1_WriteControlRegister(Contador_1_backup.CounterControlRegister);
        #endif /* (!Contador_1_ControlRegRemoved) */

    #endif /* (!Contador_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Contador_1_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Contador_1_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Contador_1_Sleep(void) 
{
    #if(!Contador_1_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Contador_1_CTRL_ENABLE == (Contador_1_CONTROL & Contador_1_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Contador_1_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Contador_1_backup.CounterEnableState = 0u;
        }
    #else
        Contador_1_backup.CounterEnableState = 1u;
        if(Contador_1_backup.CounterEnableState != 0u)
        {
            Contador_1_backup.CounterEnableState = 0u;
        }
    #endif /* (!Contador_1_ControlRegRemoved) */
    
    Contador_1_Stop();
    Contador_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Contador_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Contador_1_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Contador_1_Wakeup(void) 
{
    Contador_1_RestoreConfig();
    #if(!Contador_1_ControlRegRemoved)
        if(Contador_1_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Contador_1_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Contador_1_ControlRegRemoved) */
    
}


/* [] END OF FILE */
