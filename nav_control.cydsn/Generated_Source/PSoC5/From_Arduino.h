/*******************************************************************************
* File Name: From_Arduino.h  
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

#if !defined(CY_PINS_From_Arduino_H) /* Pins From_Arduino_H */
#define CY_PINS_From_Arduino_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "From_Arduino_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 From_Arduino__PORT == 15 && ((From_Arduino__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    From_Arduino_Write(uint8 value);
void    From_Arduino_SetDriveMode(uint8 mode);
uint8   From_Arduino_ReadDataReg(void);
uint8   From_Arduino_Read(void);
void    From_Arduino_SetInterruptMode(uint16 position, uint16 mode);
uint8   From_Arduino_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the From_Arduino_SetDriveMode() function.
     *  @{
     */
        #define From_Arduino_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define From_Arduino_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define From_Arduino_DM_RES_UP          PIN_DM_RES_UP
        #define From_Arduino_DM_RES_DWN         PIN_DM_RES_DWN
        #define From_Arduino_DM_OD_LO           PIN_DM_OD_LO
        #define From_Arduino_DM_OD_HI           PIN_DM_OD_HI
        #define From_Arduino_DM_STRONG          PIN_DM_STRONG
        #define From_Arduino_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define From_Arduino_MASK               From_Arduino__MASK
#define From_Arduino_SHIFT              From_Arduino__SHIFT
#define From_Arduino_WIDTH              1u

/* Interrupt constants */
#if defined(From_Arduino__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in From_Arduino_SetInterruptMode() function.
     *  @{
     */
        #define From_Arduino_INTR_NONE      (uint16)(0x0000u)
        #define From_Arduino_INTR_RISING    (uint16)(0x0001u)
        #define From_Arduino_INTR_FALLING   (uint16)(0x0002u)
        #define From_Arduino_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define From_Arduino_INTR_MASK      (0x01u) 
#endif /* (From_Arduino__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define From_Arduino_PS                     (* (reg8 *) From_Arduino__PS)
/* Data Register */
#define From_Arduino_DR                     (* (reg8 *) From_Arduino__DR)
/* Port Number */
#define From_Arduino_PRT_NUM                (* (reg8 *) From_Arduino__PRT) 
/* Connect to Analog Globals */                                                  
#define From_Arduino_AG                     (* (reg8 *) From_Arduino__AG)                       
/* Analog MUX bux enable */
#define From_Arduino_AMUX                   (* (reg8 *) From_Arduino__AMUX) 
/* Bidirectional Enable */                                                        
#define From_Arduino_BIE                    (* (reg8 *) From_Arduino__BIE)
/* Bit-mask for Aliased Register Access */
#define From_Arduino_BIT_MASK               (* (reg8 *) From_Arduino__BIT_MASK)
/* Bypass Enable */
#define From_Arduino_BYP                    (* (reg8 *) From_Arduino__BYP)
/* Port wide control signals */                                                   
#define From_Arduino_CTL                    (* (reg8 *) From_Arduino__CTL)
/* Drive Modes */
#define From_Arduino_DM0                    (* (reg8 *) From_Arduino__DM0) 
#define From_Arduino_DM1                    (* (reg8 *) From_Arduino__DM1)
#define From_Arduino_DM2                    (* (reg8 *) From_Arduino__DM2) 
/* Input Buffer Disable Override */
#define From_Arduino_INP_DIS                (* (reg8 *) From_Arduino__INP_DIS)
/* LCD Common or Segment Drive */
#define From_Arduino_LCD_COM_SEG            (* (reg8 *) From_Arduino__LCD_COM_SEG)
/* Enable Segment LCD */
#define From_Arduino_LCD_EN                 (* (reg8 *) From_Arduino__LCD_EN)
/* Slew Rate Control */
#define From_Arduino_SLW                    (* (reg8 *) From_Arduino__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define From_Arduino_PRTDSI__CAPS_SEL       (* (reg8 *) From_Arduino__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define From_Arduino_PRTDSI__DBL_SYNC_IN    (* (reg8 *) From_Arduino__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define From_Arduino_PRTDSI__OE_SEL0        (* (reg8 *) From_Arduino__PRTDSI__OE_SEL0) 
#define From_Arduino_PRTDSI__OE_SEL1        (* (reg8 *) From_Arduino__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define From_Arduino_PRTDSI__OUT_SEL0       (* (reg8 *) From_Arduino__PRTDSI__OUT_SEL0) 
#define From_Arduino_PRTDSI__OUT_SEL1       (* (reg8 *) From_Arduino__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define From_Arduino_PRTDSI__SYNC_OUT       (* (reg8 *) From_Arduino__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(From_Arduino__SIO_CFG)
    #define From_Arduino_SIO_HYST_EN        (* (reg8 *) From_Arduino__SIO_HYST_EN)
    #define From_Arduino_SIO_REG_HIFREQ     (* (reg8 *) From_Arduino__SIO_REG_HIFREQ)
    #define From_Arduino_SIO_CFG            (* (reg8 *) From_Arduino__SIO_CFG)
    #define From_Arduino_SIO_DIFF           (* (reg8 *) From_Arduino__SIO_DIFF)
#endif /* (From_Arduino__SIO_CFG) */

/* Interrupt Registers */
#if defined(From_Arduino__INTSTAT)
    #define From_Arduino_INTSTAT            (* (reg8 *) From_Arduino__INTSTAT)
    #define From_Arduino_SNAP               (* (reg8 *) From_Arduino__SNAP)
    
	#define From_Arduino_0_INTTYPE_REG 		(* (reg8 *) From_Arduino__0__INTTYPE)
#endif /* (From_Arduino__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_From_Arduino_H */


/* [] END OF FILE */
