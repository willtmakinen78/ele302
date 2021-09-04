/*******************************************************************************
* File Name: Servo_Clk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Servo_Clk_H)
#define CY_CLOCK_Servo_Clk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Servo_Clk_Start(void) ;
void Servo_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Servo_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Servo_Clk_StandbyPower(uint8 state) ;
void Servo_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Servo_Clk_GetDividerRegister(void) ;
void Servo_Clk_SetModeRegister(uint8 modeBitMask) ;
void Servo_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 Servo_Clk_GetModeRegister(void) ;
void Servo_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 Servo_Clk_GetSourceRegister(void) ;
#if defined(Servo_Clk__CFG3)
void Servo_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 Servo_Clk_GetPhaseRegister(void) ;
#endif /* defined(Servo_Clk__CFG3) */

#define Servo_Clk_Enable()                       Servo_Clk_Start()
#define Servo_Clk_Disable()                      Servo_Clk_Stop()
#define Servo_Clk_SetDivider(clkDivider)         Servo_Clk_SetDividerRegister(clkDivider, 1u)
#define Servo_Clk_SetDividerValue(clkDivider)    Servo_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define Servo_Clk_SetMode(clkMode)               Servo_Clk_SetModeRegister(clkMode)
#define Servo_Clk_SetSource(clkSource)           Servo_Clk_SetSourceRegister(clkSource)
#if defined(Servo_Clk__CFG3)
#define Servo_Clk_SetPhase(clkPhase)             Servo_Clk_SetPhaseRegister(clkPhase)
#define Servo_Clk_SetPhaseValue(clkPhase)        Servo_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Servo_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Servo_Clk_CLKEN              (* (reg8 *) Servo_Clk__PM_ACT_CFG)
#define Servo_Clk_CLKEN_PTR          ((reg8 *) Servo_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Servo_Clk_CLKSTBY            (* (reg8 *) Servo_Clk__PM_STBY_CFG)
#define Servo_Clk_CLKSTBY_PTR        ((reg8 *) Servo_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Servo_Clk_DIV_LSB            (* (reg8 *) Servo_Clk__CFG0)
#define Servo_Clk_DIV_LSB_PTR        ((reg8 *) Servo_Clk__CFG0)
#define Servo_Clk_DIV_PTR            ((reg16 *) Servo_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define Servo_Clk_DIV_MSB            (* (reg8 *) Servo_Clk__CFG1)
#define Servo_Clk_DIV_MSB_PTR        ((reg8 *) Servo_Clk__CFG1)

/* Mode and source configuration register */
#define Servo_Clk_MOD_SRC            (* (reg8 *) Servo_Clk__CFG2)
#define Servo_Clk_MOD_SRC_PTR        ((reg8 *) Servo_Clk__CFG2)

#if defined(Servo_Clk__CFG3)
/* Analog clock phase configuration register */
#define Servo_Clk_PHASE              (* (reg8 *) Servo_Clk__CFG3)
#define Servo_Clk_PHASE_PTR          ((reg8 *) Servo_Clk__CFG3)
#endif /* defined(Servo_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Servo_Clk_CLKEN_MASK         Servo_Clk__PM_ACT_MSK
#define Servo_Clk_CLKSTBY_MASK       Servo_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define Servo_Clk_SRC_SEL_MSK        Servo_Clk__CFG2_SRC_SEL_MASK
#define Servo_Clk_MODE_MASK          (~(Servo_Clk_SRC_SEL_MSK))

#if defined(Servo_Clk__CFG3)
/* CFG3 phase mask */
#define Servo_Clk_PHASE_MASK         Servo_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(Servo_Clk__CFG3) */

#endif /* CY_CLOCK_Servo_Clk_H */


/* [] END OF FILE */
