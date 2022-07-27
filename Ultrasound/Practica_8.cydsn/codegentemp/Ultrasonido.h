/*******************************************************************************
* File Name: Ultrasonido.h  
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

#if !defined(CY_PINS_Ultrasonido_H) /* Pins Ultrasonido_H */
#define CY_PINS_Ultrasonido_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ultrasonido_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ultrasonido__PORT == 15 && ((Ultrasonido__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ultrasonido_Write(uint8 value);
void    Ultrasonido_SetDriveMode(uint8 mode);
uint8   Ultrasonido_ReadDataReg(void);
uint8   Ultrasonido_Read(void);
void    Ultrasonido_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ultrasonido_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ultrasonido_SetDriveMode() function.
     *  @{
     */
        #define Ultrasonido_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ultrasonido_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ultrasonido_DM_RES_UP          PIN_DM_RES_UP
        #define Ultrasonido_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ultrasonido_DM_OD_LO           PIN_DM_OD_LO
        #define Ultrasonido_DM_OD_HI           PIN_DM_OD_HI
        #define Ultrasonido_DM_STRONG          PIN_DM_STRONG
        #define Ultrasonido_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ultrasonido_MASK               Ultrasonido__MASK
#define Ultrasonido_SHIFT              Ultrasonido__SHIFT
#define Ultrasonido_WIDTH              1u

/* Interrupt constants */
#if defined(Ultrasonido__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ultrasonido_SetInterruptMode() function.
     *  @{
     */
        #define Ultrasonido_INTR_NONE      (uint16)(0x0000u)
        #define Ultrasonido_INTR_RISING    (uint16)(0x0001u)
        #define Ultrasonido_INTR_FALLING   (uint16)(0x0002u)
        #define Ultrasonido_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ultrasonido_INTR_MASK      (0x01u) 
#endif /* (Ultrasonido__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ultrasonido_PS                     (* (reg8 *) Ultrasonido__PS)
/* Data Register */
#define Ultrasonido_DR                     (* (reg8 *) Ultrasonido__DR)
/* Port Number */
#define Ultrasonido_PRT_NUM                (* (reg8 *) Ultrasonido__PRT) 
/* Connect to Analog Globals */                                                  
#define Ultrasonido_AG                     (* (reg8 *) Ultrasonido__AG)                       
/* Analog MUX bux enable */
#define Ultrasonido_AMUX                   (* (reg8 *) Ultrasonido__AMUX) 
/* Bidirectional Enable */                                                        
#define Ultrasonido_BIE                    (* (reg8 *) Ultrasonido__BIE)
/* Bit-mask for Aliased Register Access */
#define Ultrasonido_BIT_MASK               (* (reg8 *) Ultrasonido__BIT_MASK)
/* Bypass Enable */
#define Ultrasonido_BYP                    (* (reg8 *) Ultrasonido__BYP)
/* Port wide control signals */                                                   
#define Ultrasonido_CTL                    (* (reg8 *) Ultrasonido__CTL)
/* Drive Modes */
#define Ultrasonido_DM0                    (* (reg8 *) Ultrasonido__DM0) 
#define Ultrasonido_DM1                    (* (reg8 *) Ultrasonido__DM1)
#define Ultrasonido_DM2                    (* (reg8 *) Ultrasonido__DM2) 
/* Input Buffer Disable Override */
#define Ultrasonido_INP_DIS                (* (reg8 *) Ultrasonido__INP_DIS)
/* LCD Common or Segment Drive */
#define Ultrasonido_LCD_COM_SEG            (* (reg8 *) Ultrasonido__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ultrasonido_LCD_EN                 (* (reg8 *) Ultrasonido__LCD_EN)
/* Slew Rate Control */
#define Ultrasonido_SLW                    (* (reg8 *) Ultrasonido__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ultrasonido_PRTDSI__CAPS_SEL       (* (reg8 *) Ultrasonido__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ultrasonido_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ultrasonido__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ultrasonido_PRTDSI__OE_SEL0        (* (reg8 *) Ultrasonido__PRTDSI__OE_SEL0) 
#define Ultrasonido_PRTDSI__OE_SEL1        (* (reg8 *) Ultrasonido__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ultrasonido_PRTDSI__OUT_SEL0       (* (reg8 *) Ultrasonido__PRTDSI__OUT_SEL0) 
#define Ultrasonido_PRTDSI__OUT_SEL1       (* (reg8 *) Ultrasonido__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ultrasonido_PRTDSI__SYNC_OUT       (* (reg8 *) Ultrasonido__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ultrasonido__SIO_CFG)
    #define Ultrasonido_SIO_HYST_EN        (* (reg8 *) Ultrasonido__SIO_HYST_EN)
    #define Ultrasonido_SIO_REG_HIFREQ     (* (reg8 *) Ultrasonido__SIO_REG_HIFREQ)
    #define Ultrasonido_SIO_CFG            (* (reg8 *) Ultrasonido__SIO_CFG)
    #define Ultrasonido_SIO_DIFF           (* (reg8 *) Ultrasonido__SIO_DIFF)
#endif /* (Ultrasonido__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ultrasonido__INTSTAT)
    #define Ultrasonido_INTSTAT            (* (reg8 *) Ultrasonido__INTSTAT)
    #define Ultrasonido_SNAP               (* (reg8 *) Ultrasonido__SNAP)
    
	#define Ultrasonido_0_INTTYPE_REG 		(* (reg8 *) Ultrasonido__0__INTTYPE)
#endif /* (Ultrasonido__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ultrasonido_H */


/* [] END OF FILE */
