/*******************************************************************************
* File Name: Input_Arduino.h  
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

#if !defined(CY_PINS_Input_Arduino_H) /* Pins Input_Arduino_H */
#define CY_PINS_Input_Arduino_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Input_Arduino_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Input_Arduino__PORT == 15 && ((Input_Arduino__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Input_Arduino_Write(uint8 value);
void    Input_Arduino_SetDriveMode(uint8 mode);
uint8   Input_Arduino_ReadDataReg(void);
uint8   Input_Arduino_Read(void);
void    Input_Arduino_SetInterruptMode(uint16 position, uint16 mode);
uint8   Input_Arduino_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Input_Arduino_SetDriveMode() function.
     *  @{
     */
        #define Input_Arduino_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Input_Arduino_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Input_Arduino_DM_RES_UP          PIN_DM_RES_UP
        #define Input_Arduino_DM_RES_DWN         PIN_DM_RES_DWN
        #define Input_Arduino_DM_OD_LO           PIN_DM_OD_LO
        #define Input_Arduino_DM_OD_HI           PIN_DM_OD_HI
        #define Input_Arduino_DM_STRONG          PIN_DM_STRONG
        #define Input_Arduino_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Input_Arduino_MASK               Input_Arduino__MASK
#define Input_Arduino_SHIFT              Input_Arduino__SHIFT
#define Input_Arduino_WIDTH              1u

/* Interrupt constants */
#if defined(Input_Arduino__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Input_Arduino_SetInterruptMode() function.
     *  @{
     */
        #define Input_Arduino_INTR_NONE      (uint16)(0x0000u)
        #define Input_Arduino_INTR_RISING    (uint16)(0x0001u)
        #define Input_Arduino_INTR_FALLING   (uint16)(0x0002u)
        #define Input_Arduino_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Input_Arduino_INTR_MASK      (0x01u) 
#endif /* (Input_Arduino__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Input_Arduino_PS                     (* (reg8 *) Input_Arduino__PS)
/* Data Register */
#define Input_Arduino_DR                     (* (reg8 *) Input_Arduino__DR)
/* Port Number */
#define Input_Arduino_PRT_NUM                (* (reg8 *) Input_Arduino__PRT) 
/* Connect to Analog Globals */                                                  
#define Input_Arduino_AG                     (* (reg8 *) Input_Arduino__AG)                       
/* Analog MUX bux enable */
#define Input_Arduino_AMUX                   (* (reg8 *) Input_Arduino__AMUX) 
/* Bidirectional Enable */                                                        
#define Input_Arduino_BIE                    (* (reg8 *) Input_Arduino__BIE)
/* Bit-mask for Aliased Register Access */
#define Input_Arduino_BIT_MASK               (* (reg8 *) Input_Arduino__BIT_MASK)
/* Bypass Enable */
#define Input_Arduino_BYP                    (* (reg8 *) Input_Arduino__BYP)
/* Port wide control signals */                                                   
#define Input_Arduino_CTL                    (* (reg8 *) Input_Arduino__CTL)
/* Drive Modes */
#define Input_Arduino_DM0                    (* (reg8 *) Input_Arduino__DM0) 
#define Input_Arduino_DM1                    (* (reg8 *) Input_Arduino__DM1)
#define Input_Arduino_DM2                    (* (reg8 *) Input_Arduino__DM2) 
/* Input Buffer Disable Override */
#define Input_Arduino_INP_DIS                (* (reg8 *) Input_Arduino__INP_DIS)
/* LCD Common or Segment Drive */
#define Input_Arduino_LCD_COM_SEG            (* (reg8 *) Input_Arduino__LCD_COM_SEG)
/* Enable Segment LCD */
#define Input_Arduino_LCD_EN                 (* (reg8 *) Input_Arduino__LCD_EN)
/* Slew Rate Control */
#define Input_Arduino_SLW                    (* (reg8 *) Input_Arduino__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Input_Arduino_PRTDSI__CAPS_SEL       (* (reg8 *) Input_Arduino__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Input_Arduino_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Input_Arduino__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Input_Arduino_PRTDSI__OE_SEL0        (* (reg8 *) Input_Arduino__PRTDSI__OE_SEL0) 
#define Input_Arduino_PRTDSI__OE_SEL1        (* (reg8 *) Input_Arduino__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Input_Arduino_PRTDSI__OUT_SEL0       (* (reg8 *) Input_Arduino__PRTDSI__OUT_SEL0) 
#define Input_Arduino_PRTDSI__OUT_SEL1       (* (reg8 *) Input_Arduino__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Input_Arduino_PRTDSI__SYNC_OUT       (* (reg8 *) Input_Arduino__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Input_Arduino__SIO_CFG)
    #define Input_Arduino_SIO_HYST_EN        (* (reg8 *) Input_Arduino__SIO_HYST_EN)
    #define Input_Arduino_SIO_REG_HIFREQ     (* (reg8 *) Input_Arduino__SIO_REG_HIFREQ)
    #define Input_Arduino_SIO_CFG            (* (reg8 *) Input_Arduino__SIO_CFG)
    #define Input_Arduino_SIO_DIFF           (* (reg8 *) Input_Arduino__SIO_DIFF)
#endif /* (Input_Arduino__SIO_CFG) */

/* Interrupt Registers */
#if defined(Input_Arduino__INTSTAT)
    #define Input_Arduino_INTSTAT            (* (reg8 *) Input_Arduino__INTSTAT)
    #define Input_Arduino_SNAP               (* (reg8 *) Input_Arduino__SNAP)
    
	#define Input_Arduino_0_INTTYPE_REG 		(* (reg8 *) Input_Arduino__0__INTTYPE)
#endif /* (Input_Arduino__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Input_Arduino_H */


/* [] END OF FILE */
