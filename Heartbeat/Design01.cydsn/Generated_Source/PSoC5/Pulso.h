/*******************************************************************************
* File Name: Pulso.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pulso_H) /* Pins Pulso_H */
#define CY_PINS_Pulso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pulso_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pulso__PORT == 15 && ((Pulso__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pulso_Write(uint8 value);
void    Pulso_SetDriveMode(uint8 mode);
uint8   Pulso_ReadDataReg(void);
uint8   Pulso_Read(void);
void    Pulso_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pulso_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pulso_SetDriveMode() function.
     *  @{
     */
        #define Pulso_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pulso_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pulso_DM_RES_UP          PIN_DM_RES_UP
        #define Pulso_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pulso_DM_OD_LO           PIN_DM_OD_LO
        #define Pulso_DM_OD_HI           PIN_DM_OD_HI
        #define Pulso_DM_STRONG          PIN_DM_STRONG
        #define Pulso_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pulso_MASK               Pulso__MASK
#define Pulso_SHIFT              Pulso__SHIFT
#define Pulso_WIDTH              1u

/* Interrupt constants */
#if defined(Pulso__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pulso_SetInterruptMode() function.
     *  @{
     */
        #define Pulso_INTR_NONE      (uint16)(0x0000u)
        #define Pulso_INTR_RISING    (uint16)(0x0001u)
        #define Pulso_INTR_FALLING   (uint16)(0x0002u)
        #define Pulso_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pulso_INTR_MASK      (0x01u) 
#endif /* (Pulso__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pulso_PS                     (* (reg8 *) Pulso__PS)
/* Data Register */
#define Pulso_DR                     (* (reg8 *) Pulso__DR)
/* Port Number */
#define Pulso_PRT_NUM                (* (reg8 *) Pulso__PRT) 
/* Connect to Analog Globals */                                                  
#define Pulso_AG                     (* (reg8 *) Pulso__AG)                       
/* Analog MUX bux enable */
#define Pulso_AMUX                   (* (reg8 *) Pulso__AMUX) 
/* Bidirectional Enable */                                                        
#define Pulso_BIE                    (* (reg8 *) Pulso__BIE)
/* Bit-mask for Aliased Register Access */
#define Pulso_BIT_MASK               (* (reg8 *) Pulso__BIT_MASK)
/* Bypass Enable */
#define Pulso_BYP                    (* (reg8 *) Pulso__BYP)
/* Port wide control signals */                                                   
#define Pulso_CTL                    (* (reg8 *) Pulso__CTL)
/* Drive Modes */
#define Pulso_DM0                    (* (reg8 *) Pulso__DM0) 
#define Pulso_DM1                    (* (reg8 *) Pulso__DM1)
#define Pulso_DM2                    (* (reg8 *) Pulso__DM2) 
/* Input Buffer Disable Override */
#define Pulso_INP_DIS                (* (reg8 *) Pulso__INP_DIS)
/* LCD Common or Segment Drive */
#define Pulso_LCD_COM_SEG            (* (reg8 *) Pulso__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pulso_LCD_EN                 (* (reg8 *) Pulso__LCD_EN)
/* Slew Rate Control */
#define Pulso_SLW                    (* (reg8 *) Pulso__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pulso_PRTDSI__CAPS_SEL       (* (reg8 *) Pulso__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pulso_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pulso__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pulso_PRTDSI__OE_SEL0        (* (reg8 *) Pulso__PRTDSI__OE_SEL0) 
#define Pulso_PRTDSI__OE_SEL1        (* (reg8 *) Pulso__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pulso_PRTDSI__OUT_SEL0       (* (reg8 *) Pulso__PRTDSI__OUT_SEL0) 
#define Pulso_PRTDSI__OUT_SEL1       (* (reg8 *) Pulso__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pulso_PRTDSI__SYNC_OUT       (* (reg8 *) Pulso__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pulso__SIO_CFG)
    #define Pulso_SIO_HYST_EN        (* (reg8 *) Pulso__SIO_HYST_EN)
    #define Pulso_SIO_REG_HIFREQ     (* (reg8 *) Pulso__SIO_REG_HIFREQ)
    #define Pulso_SIO_CFG            (* (reg8 *) Pulso__SIO_CFG)
    #define Pulso_SIO_DIFF           (* (reg8 *) Pulso__SIO_DIFF)
#endif /* (Pulso__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pulso__INTSTAT)
    #define Pulso_INTSTAT            (* (reg8 *) Pulso__INTSTAT)
    #define Pulso_SNAP               (* (reg8 *) Pulso__SNAP)
    
	#define Pulso_0_INTTYPE_REG 		(* (reg8 *) Pulso__0__INTTYPE)
#endif /* (Pulso__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pulso_H */


/* [] END OF FILE */
