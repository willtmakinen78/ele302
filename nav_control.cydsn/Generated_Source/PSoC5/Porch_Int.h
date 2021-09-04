/*******************************************************************************
* File Name: Porch_Int.h
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
#if !defined(CY_ISR_Porch_Int_H)
#define CY_ISR_Porch_Int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Porch_Int_Start(void);
void Porch_Int_StartEx(cyisraddress address);
void Porch_Int_Stop(void);

CY_ISR_PROTO(Porch_Int_Interrupt);

void Porch_Int_SetVector(cyisraddress address);
cyisraddress Porch_Int_GetVector(void);

void Porch_Int_SetPriority(uint8 priority);
uint8 Porch_Int_GetPriority(void);

void Porch_Int_Enable(void);
uint8 Porch_Int_GetState(void);
void Porch_Int_Disable(void);

void Porch_Int_SetPending(void);
void Porch_Int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Porch_Int ISR. */
#define Porch_Int_INTC_VECTOR            ((reg32 *) Porch_Int__INTC_VECT)

/* Address of the Porch_Int ISR priority. */
#define Porch_Int_INTC_PRIOR             ((reg8 *) Porch_Int__INTC_PRIOR_REG)

/* Priority of the Porch_Int interrupt. */
#define Porch_Int_INTC_PRIOR_NUMBER      Porch_Int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Porch_Int interrupt. */
#define Porch_Int_INTC_SET_EN            ((reg32 *) Porch_Int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Porch_Int interrupt. */
#define Porch_Int_INTC_CLR_EN            ((reg32 *) Porch_Int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Porch_Int interrupt state to pending. */
#define Porch_Int_INTC_SET_PD            ((reg32 *) Porch_Int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Porch_Int interrupt. */
#define Porch_Int_INTC_CLR_PD            ((reg32 *) Porch_Int__INTC_CLR_PD_REG)


#endif /* CY_ISR_Porch_Int_H */


/* [] END OF FILE */
