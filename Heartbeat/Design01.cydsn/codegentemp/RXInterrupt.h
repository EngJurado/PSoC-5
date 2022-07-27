/*******************************************************************************
* File Name: RXInterrupt.h
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
#if !defined(CY_ISR_RXInterrupt_H)
#define CY_ISR_RXInterrupt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void RXInterrupt_Start(void);
void RXInterrupt_StartEx(cyisraddress address);
void RXInterrupt_Stop(void);

CY_ISR_PROTO(RXInterrupt_Interrupt);

void RXInterrupt_SetVector(cyisraddress address);
cyisraddress RXInterrupt_GetVector(void);

void RXInterrupt_SetPriority(uint8 priority);
uint8 RXInterrupt_GetPriority(void);

void RXInterrupt_Enable(void);
uint8 RXInterrupt_GetState(void);
void RXInterrupt_Disable(void);

void RXInterrupt_SetPending(void);
void RXInterrupt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the RXInterrupt ISR. */
#define RXInterrupt_INTC_VECTOR            ((reg32 *) RXInterrupt__INTC_VECT)

/* Address of the RXInterrupt ISR priority. */
#define RXInterrupt_INTC_PRIOR             ((reg8 *) RXInterrupt__INTC_PRIOR_REG)

/* Priority of the RXInterrupt interrupt. */
#define RXInterrupt_INTC_PRIOR_NUMBER      RXInterrupt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable RXInterrupt interrupt. */
#define RXInterrupt_INTC_SET_EN            ((reg32 *) RXInterrupt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the RXInterrupt interrupt. */
#define RXInterrupt_INTC_CLR_EN            ((reg32 *) RXInterrupt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the RXInterrupt interrupt state to pending. */
#define RXInterrupt_INTC_SET_PD            ((reg32 *) RXInterrupt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the RXInterrupt interrupt. */
#define RXInterrupt_INTC_CLR_PD            ((reg32 *) RXInterrupt__INTC_CLR_PD_REG)


#endif /* CY_ISR_RXInterrupt_H */


/* [] END OF FILE */
