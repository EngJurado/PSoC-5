/*******************************************************************************
* File Name: PulsoSensor.h
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
#if !defined(CY_ISR_PulsoSensor_H)
#define CY_ISR_PulsoSensor_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PulsoSensor_Start(void);
void PulsoSensor_StartEx(cyisraddress address);
void PulsoSensor_Stop(void);

CY_ISR_PROTO(PulsoSensor_Interrupt);

void PulsoSensor_SetVector(cyisraddress address);
cyisraddress PulsoSensor_GetVector(void);

void PulsoSensor_SetPriority(uint8 priority);
uint8 PulsoSensor_GetPriority(void);

void PulsoSensor_Enable(void);
uint8 PulsoSensor_GetState(void);
void PulsoSensor_Disable(void);

void PulsoSensor_SetPending(void);
void PulsoSensor_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PulsoSensor ISR. */
#define PulsoSensor_INTC_VECTOR            ((reg32 *) PulsoSensor__INTC_VECT)

/* Address of the PulsoSensor ISR priority. */
#define PulsoSensor_INTC_PRIOR             ((reg8 *) PulsoSensor__INTC_PRIOR_REG)

/* Priority of the PulsoSensor interrupt. */
#define PulsoSensor_INTC_PRIOR_NUMBER      PulsoSensor__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PulsoSensor interrupt. */
#define PulsoSensor_INTC_SET_EN            ((reg32 *) PulsoSensor__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PulsoSensor interrupt. */
#define PulsoSensor_INTC_CLR_EN            ((reg32 *) PulsoSensor__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PulsoSensor interrupt state to pending. */
#define PulsoSensor_INTC_SET_PD            ((reg32 *) PulsoSensor__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PulsoSensor interrupt. */
#define PulsoSensor_INTC_CLR_PD            ((reg32 *) PulsoSensor__INTC_CLR_PD_REG)


#endif /* CY_ISR_PulsoSensor_H */


/* [] END OF FILE */
