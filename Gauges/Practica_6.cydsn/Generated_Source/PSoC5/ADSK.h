/*******************************************************************************
* File Name: ADSK.h  
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

#if !defined(CY_PINS_ADSK_H) /* Pins ADSK_H */
#define CY_PINS_ADSK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ADSK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ADSK__PORT == 15 && ((ADSK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ADSK_Write(uint8 value);
void    ADSK_SetDriveMode(uint8 mode);
uint8   ADSK_ReadDataReg(void);
uint8   ADSK_Read(void);
void    ADSK_SetInterruptMode(uint16 position, uint16 mode);
uint8   ADSK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ADSK_SetDriveMode() function.
     *  @{
     */
        #define ADSK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ADSK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ADSK_DM_RES_UP          PIN_DM_RES_UP
        #define ADSK_DM_RES_DWN         PIN_DM_RES_DWN
        #define ADSK_DM_OD_LO           PIN_DM_OD_LO
        #define ADSK_DM_OD_HI           PIN_DM_OD_HI
        #define ADSK_DM_STRONG          PIN_DM_STRONG
        #define ADSK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ADSK_MASK               ADSK__MASK
#define ADSK_SHIFT              ADSK__SHIFT
#define ADSK_WIDTH              1u

/* Interrupt constants */
#if defined(ADSK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ADSK_SetInterruptMode() function.
     *  @{
     */
        #define ADSK_INTR_NONE      (uint16)(0x0000u)
        #define ADSK_INTR_RISING    (uint16)(0x0001u)
        #define ADSK_INTR_FALLING   (uint16)(0x0002u)
        #define ADSK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ADSK_INTR_MASK      (0x01u) 
#endif /* (ADSK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADSK_PS                     (* (reg8 *) ADSK__PS)
/* Data Register */
#define ADSK_DR                     (* (reg8 *) ADSK__DR)
/* Port Number */
#define ADSK_PRT_NUM                (* (reg8 *) ADSK__PRT) 
/* Connect to Analog Globals */                                                  
#define ADSK_AG                     (* (reg8 *) ADSK__AG)                       
/* Analog MUX bux enable */
#define ADSK_AMUX                   (* (reg8 *) ADSK__AMUX) 
/* Bidirectional Enable */                                                        
#define ADSK_BIE                    (* (reg8 *) ADSK__BIE)
/* Bit-mask for Aliased Register Access */
#define ADSK_BIT_MASK               (* (reg8 *) ADSK__BIT_MASK)
/* Bypass Enable */
#define ADSK_BYP                    (* (reg8 *) ADSK__BYP)
/* Port wide control signals */                                                   
#define ADSK_CTL                    (* (reg8 *) ADSK__CTL)
/* Drive Modes */
#define ADSK_DM0                    (* (reg8 *) ADSK__DM0) 
#define ADSK_DM1                    (* (reg8 *) ADSK__DM1)
#define ADSK_DM2                    (* (reg8 *) ADSK__DM2) 
/* Input Buffer Disable Override */
#define ADSK_INP_DIS                (* (reg8 *) ADSK__INP_DIS)
/* LCD Common or Segment Drive */
#define ADSK_LCD_COM_SEG            (* (reg8 *) ADSK__LCD_COM_SEG)
/* Enable Segment LCD */
#define ADSK_LCD_EN                 (* (reg8 *) ADSK__LCD_EN)
/* Slew Rate Control */
#define ADSK_SLW                    (* (reg8 *) ADSK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ADSK_PRTDSI__CAPS_SEL       (* (reg8 *) ADSK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ADSK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ADSK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ADSK_PRTDSI__OE_SEL0        (* (reg8 *) ADSK__PRTDSI__OE_SEL0) 
#define ADSK_PRTDSI__OE_SEL1        (* (reg8 *) ADSK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ADSK_PRTDSI__OUT_SEL0       (* (reg8 *) ADSK__PRTDSI__OUT_SEL0) 
#define ADSK_PRTDSI__OUT_SEL1       (* (reg8 *) ADSK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ADSK_PRTDSI__SYNC_OUT       (* (reg8 *) ADSK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ADSK__SIO_CFG)
    #define ADSK_SIO_HYST_EN        (* (reg8 *) ADSK__SIO_HYST_EN)
    #define ADSK_SIO_REG_HIFREQ     (* (reg8 *) ADSK__SIO_REG_HIFREQ)
    #define ADSK_SIO_CFG            (* (reg8 *) ADSK__SIO_CFG)
    #define ADSK_SIO_DIFF           (* (reg8 *) ADSK__SIO_DIFF)
#endif /* (ADSK__SIO_CFG) */

/* Interrupt Registers */
#if defined(ADSK__INTSTAT)
    #define ADSK_INTSTAT            (* (reg8 *) ADSK__INTSTAT)
    #define ADSK_SNAP               (* (reg8 *) ADSK__SNAP)
    
	#define ADSK_0_INTTYPE_REG 		(* (reg8 *) ADSK__0__INTTYPE)
#endif /* (ADSK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ADSK_H */


/* [] END OF FILE */
