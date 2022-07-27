/*******************************************************************************
* File Name: senal.h  
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

#if !defined(CY_PINS_senal_H) /* Pins senal_H */
#define CY_PINS_senal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "senal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 senal__PORT == 15 && ((senal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    senal_Write(uint8 value);
void    senal_SetDriveMode(uint8 mode);
uint8   senal_ReadDataReg(void);
uint8   senal_Read(void);
void    senal_SetInterruptMode(uint16 position, uint16 mode);
uint8   senal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the senal_SetDriveMode() function.
     *  @{
     */
        #define senal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define senal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define senal_DM_RES_UP          PIN_DM_RES_UP
        #define senal_DM_RES_DWN         PIN_DM_RES_DWN
        #define senal_DM_OD_LO           PIN_DM_OD_LO
        #define senal_DM_OD_HI           PIN_DM_OD_HI
        #define senal_DM_STRONG          PIN_DM_STRONG
        #define senal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define senal_MASK               senal__MASK
#define senal_SHIFT              senal__SHIFT
#define senal_WIDTH              1u

/* Interrupt constants */
#if defined(senal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in senal_SetInterruptMode() function.
     *  @{
     */
        #define senal_INTR_NONE      (uint16)(0x0000u)
        #define senal_INTR_RISING    (uint16)(0x0001u)
        #define senal_INTR_FALLING   (uint16)(0x0002u)
        #define senal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define senal_INTR_MASK      (0x01u) 
#endif /* (senal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define senal_PS                     (* (reg8 *) senal__PS)
/* Data Register */
#define senal_DR                     (* (reg8 *) senal__DR)
/* Port Number */
#define senal_PRT_NUM                (* (reg8 *) senal__PRT) 
/* Connect to Analog Globals */                                                  
#define senal_AG                     (* (reg8 *) senal__AG)                       
/* Analog MUX bux enable */
#define senal_AMUX                   (* (reg8 *) senal__AMUX) 
/* Bidirectional Enable */                                                        
#define senal_BIE                    (* (reg8 *) senal__BIE)
/* Bit-mask for Aliased Register Access */
#define senal_BIT_MASK               (* (reg8 *) senal__BIT_MASK)
/* Bypass Enable */
#define senal_BYP                    (* (reg8 *) senal__BYP)
/* Port wide control signals */                                                   
#define senal_CTL                    (* (reg8 *) senal__CTL)
/* Drive Modes */
#define senal_DM0                    (* (reg8 *) senal__DM0) 
#define senal_DM1                    (* (reg8 *) senal__DM1)
#define senal_DM2                    (* (reg8 *) senal__DM2) 
/* Input Buffer Disable Override */
#define senal_INP_DIS                (* (reg8 *) senal__INP_DIS)
/* LCD Common or Segment Drive */
#define senal_LCD_COM_SEG            (* (reg8 *) senal__LCD_COM_SEG)
/* Enable Segment LCD */
#define senal_LCD_EN                 (* (reg8 *) senal__LCD_EN)
/* Slew Rate Control */
#define senal_SLW                    (* (reg8 *) senal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define senal_PRTDSI__CAPS_SEL       (* (reg8 *) senal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define senal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) senal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define senal_PRTDSI__OE_SEL0        (* (reg8 *) senal__PRTDSI__OE_SEL0) 
#define senal_PRTDSI__OE_SEL1        (* (reg8 *) senal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define senal_PRTDSI__OUT_SEL0       (* (reg8 *) senal__PRTDSI__OUT_SEL0) 
#define senal_PRTDSI__OUT_SEL1       (* (reg8 *) senal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define senal_PRTDSI__SYNC_OUT       (* (reg8 *) senal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(senal__SIO_CFG)
    #define senal_SIO_HYST_EN        (* (reg8 *) senal__SIO_HYST_EN)
    #define senal_SIO_REG_HIFREQ     (* (reg8 *) senal__SIO_REG_HIFREQ)
    #define senal_SIO_CFG            (* (reg8 *) senal__SIO_CFG)
    #define senal_SIO_DIFF           (* (reg8 *) senal__SIO_DIFF)
#endif /* (senal__SIO_CFG) */

/* Interrupt Registers */
#if defined(senal__INTSTAT)
    #define senal_INTSTAT            (* (reg8 *) senal__INTSTAT)
    #define senal_SNAP               (* (reg8 *) senal__SNAP)
    
	#define senal_0_INTTYPE_REG 		(* (reg8 *) senal__0__INTTYPE)
#endif /* (senal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_senal_H */


/* [] END OF FILE */
