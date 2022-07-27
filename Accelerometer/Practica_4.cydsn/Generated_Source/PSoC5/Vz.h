/*******************************************************************************
* File Name: Vz.h  
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

#if !defined(CY_PINS_Vz_H) /* Pins Vz_H */
#define CY_PINS_Vz_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Vz_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Vz__PORT == 15 && ((Vz__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Vz_Write(uint8 value);
void    Vz_SetDriveMode(uint8 mode);
uint8   Vz_ReadDataReg(void);
uint8   Vz_Read(void);
void    Vz_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vz_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Vz_SetDriveMode() function.
     *  @{
     */
        #define Vz_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Vz_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Vz_DM_RES_UP          PIN_DM_RES_UP
        #define Vz_DM_RES_DWN         PIN_DM_RES_DWN
        #define Vz_DM_OD_LO           PIN_DM_OD_LO
        #define Vz_DM_OD_HI           PIN_DM_OD_HI
        #define Vz_DM_STRONG          PIN_DM_STRONG
        #define Vz_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Vz_MASK               Vz__MASK
#define Vz_SHIFT              Vz__SHIFT
#define Vz_WIDTH              1u

/* Interrupt constants */
#if defined(Vz__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vz_SetInterruptMode() function.
     *  @{
     */
        #define Vz_INTR_NONE      (uint16)(0x0000u)
        #define Vz_INTR_RISING    (uint16)(0x0001u)
        #define Vz_INTR_FALLING   (uint16)(0x0002u)
        #define Vz_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Vz_INTR_MASK      (0x01u) 
#endif /* (Vz__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vz_PS                     (* (reg8 *) Vz__PS)
/* Data Register */
#define Vz_DR                     (* (reg8 *) Vz__DR)
/* Port Number */
#define Vz_PRT_NUM                (* (reg8 *) Vz__PRT) 
/* Connect to Analog Globals */                                                  
#define Vz_AG                     (* (reg8 *) Vz__AG)                       
/* Analog MUX bux enable */
#define Vz_AMUX                   (* (reg8 *) Vz__AMUX) 
/* Bidirectional Enable */                                                        
#define Vz_BIE                    (* (reg8 *) Vz__BIE)
/* Bit-mask for Aliased Register Access */
#define Vz_BIT_MASK               (* (reg8 *) Vz__BIT_MASK)
/* Bypass Enable */
#define Vz_BYP                    (* (reg8 *) Vz__BYP)
/* Port wide control signals */                                                   
#define Vz_CTL                    (* (reg8 *) Vz__CTL)
/* Drive Modes */
#define Vz_DM0                    (* (reg8 *) Vz__DM0) 
#define Vz_DM1                    (* (reg8 *) Vz__DM1)
#define Vz_DM2                    (* (reg8 *) Vz__DM2) 
/* Input Buffer Disable Override */
#define Vz_INP_DIS                (* (reg8 *) Vz__INP_DIS)
/* LCD Common or Segment Drive */
#define Vz_LCD_COM_SEG            (* (reg8 *) Vz__LCD_COM_SEG)
/* Enable Segment LCD */
#define Vz_LCD_EN                 (* (reg8 *) Vz__LCD_EN)
/* Slew Rate Control */
#define Vz_SLW                    (* (reg8 *) Vz__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Vz_PRTDSI__CAPS_SEL       (* (reg8 *) Vz__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Vz_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Vz__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Vz_PRTDSI__OE_SEL0        (* (reg8 *) Vz__PRTDSI__OE_SEL0) 
#define Vz_PRTDSI__OE_SEL1        (* (reg8 *) Vz__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Vz_PRTDSI__OUT_SEL0       (* (reg8 *) Vz__PRTDSI__OUT_SEL0) 
#define Vz_PRTDSI__OUT_SEL1       (* (reg8 *) Vz__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Vz_PRTDSI__SYNC_OUT       (* (reg8 *) Vz__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Vz__SIO_CFG)
    #define Vz_SIO_HYST_EN        (* (reg8 *) Vz__SIO_HYST_EN)
    #define Vz_SIO_REG_HIFREQ     (* (reg8 *) Vz__SIO_REG_HIFREQ)
    #define Vz_SIO_CFG            (* (reg8 *) Vz__SIO_CFG)
    #define Vz_SIO_DIFF           (* (reg8 *) Vz__SIO_DIFF)
#endif /* (Vz__SIO_CFG) */

/* Interrupt Registers */
#if defined(Vz__INTSTAT)
    #define Vz_INTSTAT            (* (reg8 *) Vz__INTSTAT)
    #define Vz_SNAP               (* (reg8 *) Vz__SNAP)
    
	#define Vz_0_INTTYPE_REG 		(* (reg8 *) Vz__0__INTTYPE)
#endif /* (Vz__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Vz_H */


/* [] END OF FILE */
