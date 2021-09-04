/*******************************************************************************
* File Name: compare_check.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_compare_check_H)
#define CY_ISR_compare_check_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void compare_check_Start(void);
void compare_check_StartEx(cyisraddress address);
void compare_check_Stop(void);

CY_ISR_PROTO(compare_check_Interrupt);

void compare_check_SetVector(cyisraddress address);
cyisraddress compare_check_GetVector(void);

void compare_check_SetPriority(uint8 priority);
uint8 compare_check_GetPriority(void);

void compare_check_Enable(void);
uint8 compare_check_GetState(void);
void compare_check_Disable(void);

void compare_check_SetPending(void);
void compare_check_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the compare_check ISR. */
#define compare_check_INTC_VECTOR            ((reg32 *) compare_check__INTC_VECT)

/* Address of the compare_check ISR priority. */
#define compare_check_INTC_PRIOR             ((reg8 *) compare_check__INTC_PRIOR_REG)

/* Priority of the compare_check interrupt. */
#define compare_check_INTC_PRIOR_NUMBER      compare_check__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable compare_check interrupt. */
#define compare_check_INTC_SET_EN            ((reg32 *) compare_check__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the compare_check interrupt. */
#define compare_check_INTC_CLR_EN            ((reg32 *) compare_check__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the compare_check interrupt state to pending. */
#define compare_check_INTC_SET_PD            ((reg32 *) compare_check__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the compare_check interrupt. */
#define compare_check_INTC_CLR_PD            ((reg32 *) compare_check__INTC_CLR_PD_REG)


#endif /* CY_ISR_compare_check_H */


/* [] END OF FILE */
