/*******************************************************************************
* File Name: Boton.h  
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

#if !defined(CY_PINS_Boton_H) /* Pins Boton_H */
#define CY_PINS_Boton_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Boton_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Boton__PORT == 15 && ((Boton__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Boton_Write(uint8 value);
void    Boton_SetDriveMode(uint8 mode);
uint8   Boton_ReadDataReg(void);
uint8   Boton_Read(void);
void    Boton_SetInterruptMode(uint16 position, uint16 mode);
uint8   Boton_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Boton_SetDriveMode() function.
     *  @{
     */
        #define Boton_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Boton_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Boton_DM_RES_UP          PIN_DM_RES_UP
        #define Boton_DM_RES_DWN         PIN_DM_RES_DWN
        #define Boton_DM_OD_LO           PIN_DM_OD_LO
        #define Boton_DM_OD_HI           PIN_DM_OD_HI
        #define Boton_DM_STRONG          PIN_DM_STRONG
        #define Boton_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Boton_MASK               Boton__MASK
#define Boton_SHIFT              Boton__SHIFT
#define Boton_WIDTH              1u

/* Interrupt constants */
#if defined(Boton__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Boton_SetInterruptMode() function.
     *  @{
     */
        #define Boton_INTR_NONE      (uint16)(0x0000u)
        #define Boton_INTR_RISING    (uint16)(0x0001u)
        #define Boton_INTR_FALLING   (uint16)(0x0002u)
        #define Boton_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Boton_INTR_MASK      (0x01u) 
#endif /* (Boton__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Boton_PS                     (* (reg8 *) Boton__PS)
/* Data Register */
#define Boton_DR                     (* (reg8 *) Boton__DR)
/* Port Number */
#define Boton_PRT_NUM                (* (reg8 *) Boton__PRT) 
/* Connect to Analog Globals */                                                  
#define Boton_AG                     (* (reg8 *) Boton__AG)                       
/* Analog MUX bux enable */
#define Boton_AMUX                   (* (reg8 *) Boton__AMUX) 
/* Bidirectional Enable */                                                        
#define Boton_BIE                    (* (reg8 *) Boton__BIE)
/* Bit-mask for Aliased Register Access */
#define Boton_BIT_MASK               (* (reg8 *) Boton__BIT_MASK)
/* Bypass Enable */
#define Boton_BYP                    (* (reg8 *) Boton__BYP)
/* Port wide control signals */                                                   
#define Boton_CTL                    (* (reg8 *) Boton__CTL)
/* Drive Modes */
#define Boton_DM0                    (* (reg8 *) Boton__DM0) 
#define Boton_DM1                    (* (reg8 *) Boton__DM1)
#define Boton_DM2                    (* (reg8 *) Boton__DM2) 
/* Input Buffer Disable Override */
#define Boton_INP_DIS                (* (reg8 *) Boton__INP_DIS)
/* LCD Common or Segment Drive */
#define Boton_LCD_COM_SEG            (* (reg8 *) Boton__LCD_COM_SEG)
/* Enable Segment LCD */
#define Boton_LCD_EN                 (* (reg8 *) Boton__LCD_EN)
/* Slew Rate Control */
#define Boton_SLW                    (* (reg8 *) Boton__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Boton_PRTDSI__CAPS_SEL       (* (reg8 *) Boton__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Boton_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Boton__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Boton_PRTDSI__OE_SEL0        (* (reg8 *) Boton__PRTDSI__OE_SEL0) 
#define Boton_PRTDSI__OE_SEL1        (* (reg8 *) Boton__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Boton_PRTDSI__OUT_SEL0       (* (reg8 *) Boton__PRTDSI__OUT_SEL0) 
#define Boton_PRTDSI__OUT_SEL1       (* (reg8 *) Boton__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Boton_PRTDSI__SYNC_OUT       (* (reg8 *) Boton__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Boton__SIO_CFG)
    #define Boton_SIO_HYST_EN        (* (reg8 *) Boton__SIO_HYST_EN)
    #define Boton_SIO_REG_HIFREQ     (* (reg8 *) Boton__SIO_REG_HIFREQ)
    #define Boton_SIO_CFG            (* (reg8 *) Boton__SIO_CFG)
    #define Boton_SIO_DIFF           (* (reg8 *) Boton__SIO_DIFF)
#endif /* (Boton__SIO_CFG) */

/* Interrupt Registers */
#if defined(Boton__INTSTAT)
    #define Boton_INTSTAT            (* (reg8 *) Boton__INTSTAT)
    #define Boton_SNAP               (* (reg8 *) Boton__SNAP)
    
	#define Boton_0_INTTYPE_REG 		(* (reg8 *) Boton__0__INTTYPE)
#endif /* (Boton__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Boton_H */


/* [] END OF FILE */
