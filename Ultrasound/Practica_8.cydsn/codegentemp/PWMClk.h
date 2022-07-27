/*******************************************************************************
* File Name: PWMClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_PWMClk_H)
#define CY_CLOCK_PWMClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void PWMClk_Start(void) ;
void PWMClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void PWMClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void PWMClk_StandbyPower(uint8 state) ;
void PWMClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 PWMClk_GetDividerRegister(void) ;
void PWMClk_SetModeRegister(uint8 modeBitMask) ;
void PWMClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 PWMClk_GetModeRegister(void) ;
void PWMClk_SetSourceRegister(uint8 clkSource) ;
uint8 PWMClk_GetSourceRegister(void) ;
#if defined(PWMClk__CFG3)
void PWMClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 PWMClk_GetPhaseRegister(void) ;
#endif /* defined(PWMClk__CFG3) */

#define PWMClk_Enable()                       PWMClk_Start()
#define PWMClk_Disable()                      PWMClk_Stop()
#define PWMClk_SetDivider(clkDivider)         PWMClk_SetDividerRegister(clkDivider, 1u)
#define PWMClk_SetDividerValue(clkDivider)    PWMClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define PWMClk_SetMode(clkMode)               PWMClk_SetModeRegister(clkMode)
#define PWMClk_SetSource(clkSource)           PWMClk_SetSourceRegister(clkSource)
#if defined(PWMClk__CFG3)
#define PWMClk_SetPhase(clkPhase)             PWMClk_SetPhaseRegister(clkPhase)
#define PWMClk_SetPhaseValue(clkPhase)        PWMClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(PWMClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define PWMClk_CLKEN              (* (reg8 *) PWMClk__PM_ACT_CFG)
#define PWMClk_CLKEN_PTR          ((reg8 *) PWMClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define PWMClk_CLKSTBY            (* (reg8 *) PWMClk__PM_STBY_CFG)
#define PWMClk_CLKSTBY_PTR        ((reg8 *) PWMClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define PWMClk_DIV_LSB            (* (reg8 *) PWMClk__CFG0)
#define PWMClk_DIV_LSB_PTR        ((reg8 *) PWMClk__CFG0)
#define PWMClk_DIV_PTR            ((reg16 *) PWMClk__CFG0)

/* Clock MSB divider configuration register. */
#define PWMClk_DIV_MSB            (* (reg8 *) PWMClk__CFG1)
#define PWMClk_DIV_MSB_PTR        ((reg8 *) PWMClk__CFG1)

/* Mode and source configuration register */
#define PWMClk_MOD_SRC            (* (reg8 *) PWMClk__CFG2)
#define PWMClk_MOD_SRC_PTR        ((reg8 *) PWMClk__CFG2)

#if defined(PWMClk__CFG3)
/* Analog clock phase configuration register */
#define PWMClk_PHASE              (* (reg8 *) PWMClk__CFG3)
#define PWMClk_PHASE_PTR          ((reg8 *) PWMClk__CFG3)
#endif /* defined(PWMClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define PWMClk_CLKEN_MASK         PWMClk__PM_ACT_MSK
#define PWMClk_CLKSTBY_MASK       PWMClk__PM_STBY_MSK

/* CFG2 field masks */
#define PWMClk_SRC_SEL_MSK        PWMClk__CFG2_SRC_SEL_MASK
#define PWMClk_MODE_MASK          (~(PWMClk_SRC_SEL_MSK))

#if defined(PWMClk__CFG3)
/* CFG3 phase mask */
#define PWMClk_PHASE_MASK         PWMClk__CFG3_PHASE_DLY_MASK
#endif /* defined(PWMClk__CFG3) */

#endif /* CY_CLOCK_PWMClk_H */


/* [] END OF FILE */
