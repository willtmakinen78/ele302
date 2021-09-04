/*******************************************************************************
* File Name: Hall.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Hall_ALIASES_H) /* Pins Hall_ALIASES_H */
#define CY_PINS_Hall_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Hall_0			(Hall__0__PC)
#define Hall_0_INTR	((uint16)((uint16)0x0001u << Hall__0__SHIFT))

#define Hall_INTR_ALL	 ((uint16)(Hall_0_INTR))

#endif /* End Pins Hall_ALIASES_H */


/* [] END OF FILE */
