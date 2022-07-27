/*******************************************************************************
* File Name: ADDO.h  
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

#if !defined(CY_PINS_ADDO_H) /* Pins ADDO_H */
#define CY_PINS_ADDO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADDO_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADDO__PORT == 15 && ((ADDO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADDO_Write(uint8 value);
void    ADDO_SetDriveMode(uint8 mode);
uint8   ADDO_ReadDataReg(void);
uint8   ADDO_Read(void);
void    ADDO_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADDO_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADDO_SetDriveMode() function.
     *  @{
     */
        #define ADDO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADDO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADDO_DM_RES_UP          PIN_DM_RES_UP
        #define ADDO_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADDO_DM_OD_LO           PIN_DM_OD_LO
        #define ADDO_DM_OD_HI           PIN_DM_OD_HI
        #define ADDO_DM_STRONG          PIN_DM_STRONG
        #define ADDO_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADDO_MASK               ADDO__MASK
#define ADDO_SHIFT              ADDO__SHIFT
#define ADDO_WIDTH              1u

/* Interrupt constants */
#if defined(ADDO__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADDO_SetInterruptMode() function.
     *  @{
     */
        #define ADDO_INTR_NONE      (uint16)(0x0000u)
        #define ADDO_INTR_RISING    (uint16)(0x0001u)
        #define ADDO_INTR_FALLING   (uint16)(0x0002u)
        #define ADDO_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADDO_INTR_MASK      (0x01u) 
#endif /* (ADDO__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADDO_PS                     (* (reg8 *) ADDO__PS)
/* Data Register */
#define ADDO_DR                     (* (reg8 *) ADDO__DR)
/* Port Number */
#define ADDO_PRT_NUM                (* (reg8 *) ADDO__PRT) 
/* Connect to Analog Globals */                                                  
#define ADDO_AG                     (* (reg8 *) ADDO__AG)                       
/* Analog MUX bux enable */
#define ADDO_AMUX                   (* (reg8 *) ADDO__AMUX) 
/* Bidirectional Enable */                                                        
#define ADDO_BIE                    (* (reg8 *) ADDO__BIE)
/* Bit-mask for Aliased Register Access */
#define ADDO_BIT_MASK               (* (reg8 *) ADDO__BIT_MASK)
/* Bypass Enable */
#define ADDO_BYP                    (* (reg8 *) ADDO__BYP)
/* Port wide control signals */                                                   
#define ADDO_CTL                    (* (reg8 *) ADDO__CTL)
/* Drive Modes */
#define ADDO_DM0                    (* (reg8 *) ADDO__DM0) 
#define ADDO_DM1                    (* (reg8 *) ADDO__DM1)
#define ADDO_DM2                    (* (reg8 *) ADDO__DM2) 
/* Input Buffer Disable Override */
#define ADDO_INP_DIS                (* (reg8 *) ADDO__INP_DIS)
/* LCD Common or Segment Drive */
#define ADDO_LCD_COM_SEG            (* (reg8 *) ADDO__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADDO_LCD_EN                 (* (reg8 *) ADDO__LCD_EN)
/* Slew Rate Control */
#define ADDO_SLW                    (* (reg8 *) ADDO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADDO_PRTDSI__CAPS_SEL       (* (reg8 *) ADDO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADDO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADDO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADDO_PRTDSI__OE_SEL0        (* (reg8 *) ADDO__PRTDSI__OE_SEL0) 
#define ADDO_PRTDSI__OE_SEL1        (* (reg8 *) ADDO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADDO_PRTDSI__OUT_SEL0       (* (reg8 *) ADDO__PRTDSI__OUT_SEL0) 
#define ADDO_PRTDSI__OUT_SEL1       (* (reg8 *) ADDO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADDO_PRTDSI__SYNC_OUT       (* (reg8 *) ADDO__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADDO__SIO_CFG)
    #define ADDO_SIO_HYST_EN        (* (reg8 *) ADDO__SIO_HYST_EN)
    #define ADDO_SIO_REG_HIFREQ     (* (reg8 *) ADDO__SIO_REG_HIFREQ)
    #define ADDO_SIO_CFG            (* (reg8 *) ADDO__SIO_CFG)
    #define ADDO_SIO_DIFF           (* (reg8 *) ADDO__SIO_DIFF)
#endif /* (ADDO__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADDO__INTSTAT)
    #define ADDO_INTSTAT            (* (reg8 *) ADDO__INTSTAT)
    #define ADDO_SNAP               (* (reg8 *) ADDO__SNAP)
    
	#define ADDO_0_INTTYPE_REG 		(* (reg8 *) ADDO__0__INTTYPE)
#endif /* (ADDO__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADDO_H */


/* [] END OF FILE */
