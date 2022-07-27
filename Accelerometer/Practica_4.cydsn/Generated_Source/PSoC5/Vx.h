/*******************************************************************************
* File Name: Vx.h  
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

#if !defined(CY_PINS_Vx_H) /* Pins Vx_H */
#define CY_PINS_Vx_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vx_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vx__PORT == 15 && ((Vx__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vx_Write(uint8 value);
void    Vx_SetDriveMode(uint8 mode);
uint8   Vx_ReadDataReg(void);
uint8   Vx_Read(void);
void    Vx_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vx_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vx_SetDriveMode() function.
     *  @{
     */
        #define Vx_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vx_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vx_DM_RES_UP          PIN_DM_RES_UP
        #define Vx_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vx_DM_OD_LO           PIN_DM_OD_LO
        #define Vx_DM_OD_HI           PIN_DM_OD_HI
        #define Vx_DM_STRONG          PIN_DM_STRONG
        #define Vx_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vx_MASK               Vx__MASK
#define Vx_SHIFT              Vx__SHIFT
#define Vx_WIDTH              1u

/* Interrupt constants */
#if defined(Vx__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vx_SetInterruptMode() function.
     *  @{
     */
        #define Vx_INTR_NONE      (uint16)(0x0000u)
        #define Vx_INTR_RISING    (uint16)(0x0001u)
        #define Vx_INTR_FALLING   (uint16)(0x0002u)
        #define Vx_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vx_INTR_MASK      (0x01u) 
#endif /* (Vx__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vx_PS                     (* (reg8 *) Vx__PS)
/* Data Register */
#define Vx_DR                     (* (reg8 *) Vx__DR)
/* Port Number */
#define Vx_PRT_NUM                (* (reg8 *) Vx__PRT) 
/* Connect to Analog Globals */                                                  
#define Vx_AG                     (* (reg8 *) Vx__AG)                       
/* Analog MUX bux enable */
#define Vx_AMUX                   (* (reg8 *) Vx__AMUX) 
/* Bidirectional Enable */                                                        
#define Vx_BIE                    (* (reg8 *) Vx__BIE)
/* Bit-mask for Aliased Register Access */
#define Vx_BIT_MASK               (* (reg8 *) Vx__BIT_MASK)
/* Bypass Enable */
#define Vx_BYP                    (* (reg8 *) Vx__BYP)
/* Port wide control signals */                                                   
#define Vx_CTL                    (* (reg8 *) Vx__CTL)
/* Drive Modes */
#define Vx_DM0                    (* (reg8 *) Vx__DM0) 
#define Vx_DM1                    (* (reg8 *) Vx__DM1)
#define Vx_DM2                    (* (reg8 *) Vx__DM2) 
/* Input Buffer Disable Override */
#define Vx_INP_DIS                (* (reg8 *) Vx__INP_DIS)
/* LCD Common or Segment Drive */
#define Vx_LCD_COM_SEG            (* (reg8 *) Vx__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vx_LCD_EN                 (* (reg8 *) Vx__LCD_EN)
/* Slew Rate Control */
#define Vx_SLW                    (* (reg8 *) Vx__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vx_PRTDSI__CAPS_SEL       (* (reg8 *) Vx__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vx_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vx__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vx_PRTDSI__OE_SEL0        (* (reg8 *) Vx__PRTDSI__OE_SEL0) 
#define Vx_PRTDSI__OE_SEL1        (* (reg8 *) Vx__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vx_PRTDSI__OUT_SEL0       (* (reg8 *) Vx__PRTDSI__OUT_SEL0) 
#define Vx_PRTDSI__OUT_SEL1       (* (reg8 *) Vx__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vx_PRTDSI__SYNC_OUT       (* (reg8 *) Vx__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vx__SIO_CFG)
    #define Vx_SIO_HYST_EN        (* (reg8 *) Vx__SIO_HYST_EN)
    #define Vx_SIO_REG_HIFREQ     (* (reg8 *) Vx__SIO_REG_HIFREQ)
    #define Vx_SIO_CFG            (* (reg8 *) Vx__SIO_CFG)
    #define Vx_SIO_DIFF           (* (reg8 *) Vx__SIO_DIFF)
#endif /* (Vx__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vx__INTSTAT)
    #define Vx_INTSTAT            (* (reg8 *) Vx__INTSTAT)
    #define Vx_SNAP               (* (reg8 *) Vx__SNAP)
    
	#define Vx_0_INTTYPE_REG 		(* (reg8 *) Vx__0__INTTYPE)
#endif /* (Vx__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vx_H */


/* [] END OF FILE */
