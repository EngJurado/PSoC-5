/*******************************************************************************
* File Name: Vy.h  
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

#if !defined(CY_PINS_Vy_H) /* Pins Vy_H */
#define CY_PINS_Vy_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vy_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vy__PORT == 15 && ((Vy__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vy_Write(uint8 value);
void    Vy_SetDriveMode(uint8 mode);
uint8   Vy_ReadDataReg(void);
uint8   Vy_Read(void);
void    Vy_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vy_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vy_SetDriveMode() function.
     *  @{
     */
        #define Vy_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vy_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vy_DM_RES_UP          PIN_DM_RES_UP
        #define Vy_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vy_DM_OD_LO           PIN_DM_OD_LO
        #define Vy_DM_OD_HI           PIN_DM_OD_HI
        #define Vy_DM_STRONG          PIN_DM_STRONG
        #define Vy_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vy_MASK               Vy__MASK
#define Vy_SHIFT              Vy__SHIFT
#define Vy_WIDTH              1u

/* Interrupt constants */
#if defined(Vy__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vy_SetInterruptMode() function.
     *  @{
     */
        #define Vy_INTR_NONE      (uint16)(0x0000u)
        #define Vy_INTR_RISING    (uint16)(0x0001u)
        #define Vy_INTR_FALLING   (uint16)(0x0002u)
        #define Vy_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vy_INTR_MASK      (0x01u) 
#endif /* (Vy__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vy_PS                     (* (reg8 *) Vy__PS)
/* Data Register */
#define Vy_DR                     (* (reg8 *) Vy__DR)
/* Port Number */
#define Vy_PRT_NUM                (* (reg8 *) Vy__PRT) 
/* Connect to Analog Globals */                                                  
#define Vy_AG                     (* (reg8 *) Vy__AG)                       
/* Analog MUX bux enable */
#define Vy_AMUX                   (* (reg8 *) Vy__AMUX) 
/* Bidirectional Enable */                                                        
#define Vy_BIE                    (* (reg8 *) Vy__BIE)
/* Bit-mask for Aliased Register Access */
#define Vy_BIT_MASK               (* (reg8 *) Vy__BIT_MASK)
/* Bypass Enable */
#define Vy_BYP                    (* (reg8 *) Vy__BYP)
/* Port wide control signals */                                                   
#define Vy_CTL                    (* (reg8 *) Vy__CTL)
/* Drive Modes */
#define Vy_DM0                    (* (reg8 *) Vy__DM0) 
#define Vy_DM1                    (* (reg8 *) Vy__DM1)
#define Vy_DM2                    (* (reg8 *) Vy__DM2) 
/* Input Buffer Disable Override */
#define Vy_INP_DIS                (* (reg8 *) Vy__INP_DIS)
/* LCD Common or Segment Drive */
#define Vy_LCD_COM_SEG            (* (reg8 *) Vy__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vy_LCD_EN                 (* (reg8 *) Vy__LCD_EN)
/* Slew Rate Control */
#define Vy_SLW                    (* (reg8 *) Vy__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vy_PRTDSI__CAPS_SEL       (* (reg8 *) Vy__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vy_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vy__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vy_PRTDSI__OE_SEL0        (* (reg8 *) Vy__PRTDSI__OE_SEL0) 
#define Vy_PRTDSI__OE_SEL1        (* (reg8 *) Vy__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vy_PRTDSI__OUT_SEL0       (* (reg8 *) Vy__PRTDSI__OUT_SEL0) 
#define Vy_PRTDSI__OUT_SEL1       (* (reg8 *) Vy__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vy_PRTDSI__SYNC_OUT       (* (reg8 *) Vy__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vy__SIO_CFG)
    #define Vy_SIO_HYST_EN        (* (reg8 *) Vy__SIO_HYST_EN)
    #define Vy_SIO_REG_HIFREQ     (* (reg8 *) Vy__SIO_REG_HIFREQ)
    #define Vy_SIO_CFG            (* (reg8 *) Vy__SIO_CFG)
    #define Vy_SIO_DIFF           (* (reg8 *) Vy__SIO_DIFF)
#endif /* (Vy__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vy__INTSTAT)
    #define Vy_INTSTAT            (* (reg8 *) Vy__INTSTAT)
    #define Vy_SNAP               (* (reg8 *) Vy__SNAP)
    
	#define Vy_0_INTTYPE_REG 		(* (reg8 *) Vy__0__INTTYPE)
#endif /* (Vy__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vy_H */


/* [] END OF FILE */
