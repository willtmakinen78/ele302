/*******************************************************************************
* File Name: SERVO_output.h  
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

#if !defined(CY_PINS_SERVO_output_H) /* Pins SERVO_output_H */
#define CY_PINS_SERVO_output_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SERVO_output_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SERVO_output__PORT == 15 && ((SERVO_output__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SERVO_output_Write(uint8 value);
void    SERVO_output_SetDriveMode(uint8 mode);
uint8   SERVO_output_ReadDataReg(void);
uint8   SERVO_output_Read(void);
void    SERVO_output_SetInterruptMode(uint16 position, uint16 mode);
uint8   SERVO_output_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SERVO_output_SetDriveMode() function.
     *  @{
     */
        #define SERVO_output_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SERVO_output_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SERVO_output_DM_RES_UP          PIN_DM_RES_UP
        #define SERVO_output_DM_RES_DWN         PIN_DM_RES_DWN
        #define SERVO_output_DM_OD_LO           PIN_DM_OD_LO
        #define SERVO_output_DM_OD_HI           PIN_DM_OD_HI
        #define SERVO_output_DM_STRONG          PIN_DM_STRONG
        #define SERVO_output_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SERVO_output_MASK               SERVO_output__MASK
#define SERVO_output_SHIFT              SERVO_output__SHIFT
#define SERVO_output_WIDTH              1u

/* Interrupt constants */
#if defined(SERVO_output__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SERVO_output_SetInterruptMode() function.
     *  @{
     */
        #define SERVO_output_INTR_NONE      (uint16)(0x0000u)
        #define SERVO_output_INTR_RISING    (uint16)(0x0001u)
        #define SERVO_output_INTR_FALLING   (uint16)(0x0002u)
        #define SERVO_output_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SERVO_output_INTR_MASK      (0x01u) 
#endif /* (SERVO_output__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SERVO_output_PS                     (* (reg8 *) SERVO_output__PS)
/* Data Register */
#define SERVO_output_DR                     (* (reg8 *) SERVO_output__DR)
/* Port Number */
#define SERVO_output_PRT_NUM                (* (reg8 *) SERVO_output__PRT) 
/* Connect to Analog Globals */                                                  
#define SERVO_output_AG                     (* (reg8 *) SERVO_output__AG)                       
/* Analog MUX bux enable */
#define SERVO_output_AMUX                   (* (reg8 *) SERVO_output__AMUX) 
/* Bidirectional Enable */                                                        
#define SERVO_output_BIE                    (* (reg8 *) SERVO_output__BIE)
/* Bit-mask for Aliased Register Access */
#define SERVO_output_BIT_MASK               (* (reg8 *) SERVO_output__BIT_MASK)
/* Bypass Enable */
#define SERVO_output_BYP                    (* (reg8 *) SERVO_output__BYP)
/* Port wide control signals */                                                   
#define SERVO_output_CTL                    (* (reg8 *) SERVO_output__CTL)
/* Drive Modes */
#define SERVO_output_DM0                    (* (reg8 *) SERVO_output__DM0) 
#define SERVO_output_DM1                    (* (reg8 *) SERVO_output__DM1)
#define SERVO_output_DM2                    (* (reg8 *) SERVO_output__DM2) 
/* Input Buffer Disable Override */
#define SERVO_output_INP_DIS                (* (reg8 *) SERVO_output__INP_DIS)
/* LCD Common or Segment Drive */
#define SERVO_output_LCD_COM_SEG            (* (reg8 *) SERVO_output__LCD_COM_SEG)
/* Enable Segment LCD */
#define SERVO_output_LCD_EN                 (* (reg8 *) SERVO_output__LCD_EN)
/* Slew Rate Control */
#define SERVO_output_SLW                    (* (reg8 *) SERVO_output__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SERVO_output_PRTDSI__CAPS_SEL       (* (reg8 *) SERVO_output__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SERVO_output_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SERVO_output__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SERVO_output_PRTDSI__OE_SEL0        (* (reg8 *) SERVO_output__PRTDSI__OE_SEL0) 
#define SERVO_output_PRTDSI__OE_SEL1        (* (reg8 *) SERVO_output__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SERVO_output_PRTDSI__OUT_SEL0       (* (reg8 *) SERVO_output__PRTDSI__OUT_SEL0) 
#define SERVO_output_PRTDSI__OUT_SEL1       (* (reg8 *) SERVO_output__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SERVO_output_PRTDSI__SYNC_OUT       (* (reg8 *) SERVO_output__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SERVO_output__SIO_CFG)
    #define SERVO_output_SIO_HYST_EN        (* (reg8 *) SERVO_output__SIO_HYST_EN)
    #define SERVO_output_SIO_REG_HIFREQ     (* (reg8 *) SERVO_output__SIO_REG_HIFREQ)
    #define SERVO_output_SIO_CFG            (* (reg8 *) SERVO_output__SIO_CFG)
    #define SERVO_output_SIO_DIFF           (* (reg8 *) SERVO_output__SIO_DIFF)
#endif /* (SERVO_output__SIO_CFG) */

/* Interrupt Registers */
#if defined(SERVO_output__INTSTAT)
    #define SERVO_output_INTSTAT            (* (reg8 *) SERVO_output__INTSTAT)
    #define SERVO_output_SNAP               (* (reg8 *) SERVO_output__SNAP)
    
	#define SERVO_output_0_INTTYPE_REG 		(* (reg8 *) SERVO_output__0__INTTYPE)
#endif /* (SERVO_output__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SERVO_output_H */


/* [] END OF FILE */
