/*******************************************************************************
* File Name: H_Sync_Int.h
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
#if !defined(CY_ISR_H_Sync_Int_H)
#define CY_ISR_H_Sync_Int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void H_Sync_Int_Start(void);
void H_Sync_Int_StartEx(cyisraddress address);
void H_Sync_Int_Stop(void);

CY_ISR_PROTO(H_Sync_Int_Interrupt);

void H_Sync_Int_SetVector(cyisraddress address);
cyisraddress H_Sync_Int_GetVector(void);

void H_Sync_Int_SetPriority(uint8 priority);
uint8 H_Sync_Int_GetPriority(void);

void H_Sync_Int_Enable(void);
uint8 H_Sync_Int_GetState(void);
void H_Sync_Int_Disable(void);

void H_Sync_Int_SetPending(void);
void H_Sync_Int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the H_Sync_Int ISR. */
#define H_Sync_Int_INTC_VECTOR            ((reg32 *) H_Sync_Int__INTC_VECT)

/* Address of the H_Sync_Int ISR priority. */
#define H_Sync_Int_INTC_PRIOR             ((reg8 *) H_Sync_Int__INTC_PRIOR_REG)

/* Priority of the H_Sync_Int interrupt. */
#define H_Sync_Int_INTC_PRIOR_NUMBER      H_Sync_Int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable H_Sync_Int interrupt. */
#define H_Sync_Int_INTC_SET_EN            ((reg32 *) H_Sync_Int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the H_Sync_Int interrupt. */
#define H_Sync_Int_INTC_CLR_EN            ((reg32 *) H_Sync_Int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the H_Sync_Int interrupt state to pending. */
#define H_Sync_Int_INTC_SET_PD            ((reg32 *) H_Sync_Int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the H_Sync_Int interrupt. */
#define H_Sync_Int_INTC_CLR_PD            ((reg32 *) H_Sync_Int__INTC_CLR_PD_REG)


#endif /* CY_ISR_H_Sync_Int_H */


/* [] END OF FILE */
