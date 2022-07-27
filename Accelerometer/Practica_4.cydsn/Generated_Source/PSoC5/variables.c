/*******************************************************************************
* File Name: variables.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "variables.h"

static uint8 variables_lastChannel = variables_NULL_CHANNEL;


/*******************************************************************************
* Function Name: variables_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void variables_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < variables_CHANNELS ; chan++)
    {
#if (variables_MUXTYPE == variables_MUX_SINGLE)
        variables_Unset(chan);
#else
        variables_CYAMUXSIDE_A_Unset(chan);
        variables_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    variables_lastChannel = variables_NULL_CHANNEL;
}


#if (!variables_ATMOSTONE)
/*******************************************************************************
* Function Name: variables_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void variables_Select(uint8 channel) 
{
    variables_DisconnectAll();        /* Disconnect all previous connections */
    variables_Connect(channel);       /* Make the given selection */
    variables_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: variables_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void variables_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( variables_lastChannel != variables_NULL_CHANNEL)
    {
        variables_Disconnect(variables_lastChannel);
    }

    /* Make the new channel connection */
#if (variables_MUXTYPE == variables_MUX_SINGLE)
    variables_Set(channel);
#else
    variables_CYAMUXSIDE_A_Set(channel);
    variables_CYAMUXSIDE_B_Set(channel);
#endif


    variables_lastChannel = channel;   /* Update last channel */
}


#if (variables_MUXTYPE == variables_MUX_DIFF)
#if (!variables_ATMOSTONE)
/*******************************************************************************
* Function Name: variables_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void variables_Connect(uint8 channel) 
{
    variables_CYAMUXSIDE_A_Set(channel);
    variables_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: variables_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void variables_Disconnect(uint8 channel) 
{
    variables_CYAMUXSIDE_A_Unset(channel);
    variables_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (variables_ATMOSTONE)
/*******************************************************************************
* Function Name: variables_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void variables_DisconnectAll(void) 
{
    if(variables_lastChannel != variables_NULL_CHANNEL) 
    {
        variables_Disconnect(variables_lastChannel);
        variables_lastChannel = variables_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
