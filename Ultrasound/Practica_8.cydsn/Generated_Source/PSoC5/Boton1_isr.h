/*******************************************************************************
* File Name: Boton1_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Boton1_isr_H)
#define CY_ISR_Boton1_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Boton1_isr_Start(void);
void Boton1_isr_StartEx(cyisraddress address);
void Boton1_isr_Stop(void);

CY_ISR_PROTO(Boton1_isr_Interrupt);

void Boton1_isr_SetVector(cyisraddress address);
cyisraddress Boton1_isr_GetVector(void);

void Boton1_isr_SetPriority(uint8 priority);
uint8 Boton1_isr_GetPriority(void);

void Boton1_isr_Enable(void);
uint8 Boton1_isr_GetState(void);
void Boton1_isr_Disable(void);

void Boton1_isr_SetPending(void);
void Boton1_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Boton1_isr ISR. */
#define Boton1_isr_INTC_VECTOR            ((reg32 *) Boton1_isr__INTC_VECT)

/* Address of the Boton1_isr ISR priority. */
#define Boton1_isr_INTC_PRIOR             ((reg8 *) Boton1_isr__INTC_PRIOR_REG)

/* Priority of the Boton1_isr interrupt. */
#define Boton1_isr_INTC_PRIOR_NUMBER      Boton1_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Boton1_isr interrupt. */
#define Boton1_isr_INTC_SET_EN            ((reg32 *) Boton1_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Boton1_isr interrupt. */
#define Boton1_isr_INTC_CLR_EN            ((reg32 *) Boton1_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Boton1_isr interrupt state to pending. */
#define Boton1_isr_INTC_SET_PD            ((reg32 *) Boton1_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Boton1_isr interrupt. */
#define Boton1_isr_INTC_CLR_PD            ((reg32 *) Boton1_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_Boton1_isr_H */


/* [] END OF FILE */
