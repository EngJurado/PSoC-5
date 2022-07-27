/*******************************************************************************
* File Name: variables.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_variables_H)
#define CY_AMUX_variables_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void variables_Start(void) ;
#define variables_Init() variables_Start()
void variables_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void variables_Stop(void); */
/* void variables_Select(uint8 channel); */
/* void variables_Connect(uint8 channel); */
/* void variables_Disconnect(uint8 channel); */
/* void variables_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define variables_CHANNELS  3u
#define variables_MUXTYPE   1
#define variables_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define variables_NULL_CHANNEL 0xFFu
#define variables_MUX_SINGLE   1
#define variables_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if variables_MUXTYPE == variables_MUX_SINGLE
# if !variables_ATMOSTONE
#  define variables_Connect(channel) variables_Set(channel)
# endif
# define variables_Disconnect(channel) variables_Unset(channel)
#else
# if !variables_ATMOSTONE
void variables_Connect(uint8 channel) ;
# endif
void variables_Disconnect(uint8 channel) ;
#endif

#if variables_ATMOSTONE
# define variables_Stop() variables_DisconnectAll()
# define variables_Select(channel) variables_FastSelect(channel)
void variables_DisconnectAll(void) ;
#else
# define variables_Stop() variables_Start()
void variables_Select(uint8 channel) ;
# define variables_DisconnectAll() variables_Start()
#endif

#endif /* CY_AMUX_variables_H */


/* [] END OF FILE */
