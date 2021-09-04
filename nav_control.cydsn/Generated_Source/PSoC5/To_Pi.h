/*******************************************************************************
* File Name: To_Pi.h  
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

#if !defined(CY_PINS_To_Pi_H) /* Pins To_Pi_H */
#define CY_PINS_To_Pi_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "To_Pi_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 To_Pi__PORT == 15 && ((To_Pi__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    To_Pi_Write(uint8 value);
void    To_Pi_SetDriveMode(uint8 mode);
uint8   To_Pi_ReadDataReg(void);
uint8   To_Pi_Read(void);
void    To_Pi_SetInterruptMode(uint16 position, uint16 mode);
uint8   To_Pi_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the To_Pi_SetDriveMode() function.
     *  @{
     */
        #define To_Pi_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define To_Pi_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define To_Pi_DM_RES_UP          PIN_DM_RES_UP
        #define To_Pi_DM_RES_DWN         PIN_DM_RES_DWN
        #define To_Pi_DM_OD_LO           PIN_DM_OD_LO
        #define To_Pi_DM_OD_HI           PIN_DM_OD_HI
        #define To_Pi_DM_STRONG          PIN_DM_STRONG
        #define To_Pi_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define To_Pi_MASK               To_Pi__MASK
#define To_Pi_SHIFT              To_Pi__SHIFT
#define To_Pi_WIDTH              1u

/* Interrupt constants */
#if defined(To_Pi__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in To_Pi_SetInterruptMode() function.
     *  @{
     */
        #define To_Pi_INTR_NONE      (uint16)(0x0000u)
        #define To_Pi_INTR_RISING    (uint16)(0x0001u)
        #define To_Pi_INTR_FALLING   (uint16)(0x0002u)
        #define To_Pi_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define To_Pi_INTR_MASK      (0x01u) 
#endif /* (To_Pi__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define To_Pi_PS                     (* (reg8 *) To_Pi__PS)
/* Data Register */
#define To_Pi_DR                     (* (reg8 *) To_Pi__DR)
/* Port Number */
#define To_Pi_PRT_NUM                (* (reg8 *) To_Pi__PRT) 
/* Connect to Analog Globals */                                                  
#define To_Pi_AG                     (* (reg8 *) To_Pi__AG)                       
/* Analog MUX bux enable */
#define To_Pi_AMUX                   (* (reg8 *) To_Pi__AMUX) 
/* Bidirectional Enable */                                                        
#define To_Pi_BIE                    (* (reg8 *) To_Pi__BIE)
/* Bit-mask for Aliased Register Access */
#define To_Pi_BIT_MASK               (* (reg8 *) To_Pi__BIT_MASK)
/* Bypass Enable */
#define To_Pi_BYP                    (* (reg8 *) To_Pi__BYP)
/* Port wide control signals */                                                   
#define To_Pi_CTL                    (* (reg8 *) To_Pi__CTL)
/* Drive Modes */
#define To_Pi_DM0                    (* (reg8 *) To_Pi__DM0) 
#define To_Pi_DM1                    (* (reg8 *) To_Pi__DM1)
#define To_Pi_DM2                    (* (reg8 *) To_Pi__DM2) 
/* Input Buffer Disable Override */
#define To_Pi_INP_DIS                (* (reg8 *) To_Pi__INP_DIS)
/* LCD Common or Segment Drive */
#define To_Pi_LCD_COM_SEG            (* (reg8 *) To_Pi__LCD_COM_SEG)
/* Enable Segment LCD */
#define To_Pi_LCD_EN                 (* (reg8 *) To_Pi__LCD_EN)
/* Slew Rate Control */
#define To_Pi_SLW                    (* (reg8 *) To_Pi__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define To_Pi_PRTDSI__CAPS_SEL       (* (reg8 *) To_Pi__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define To_Pi_PRTDSI__DBL_SYNC_IN    (* (reg8 *) To_Pi__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define To_Pi_PRTDSI__OE_SEL0        (* (reg8 *) To_Pi__PRTDSI__OE_SEL0) 
#define To_Pi_PRTDSI__OE_SEL1        (* (reg8 *) To_Pi__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define To_Pi_PRTDSI__OUT_SEL0       (* (reg8 *) To_Pi__PRTDSI__OUT_SEL0) 
#define To_Pi_PRTDSI__OUT_SEL1       (* (reg8 *) To_Pi__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define To_Pi_PRTDSI__SYNC_OUT       (* (reg8 *) To_Pi__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(To_Pi__SIO_CFG)
    #define To_Pi_SIO_HYST_EN        (* (reg8 *) To_Pi__SIO_HYST_EN)
    #define To_Pi_SIO_REG_HIFREQ     (* (reg8 *) To_Pi__SIO_REG_HIFREQ)
    #define To_Pi_SIO_CFG            (* (reg8 *) To_Pi__SIO_CFG)
    #define To_Pi_SIO_DIFF           (* (reg8 *) To_Pi__SIO_DIFF)
#endif /* (To_Pi__SIO_CFG) */

/* Interrupt Registers */
#if defined(To_Pi__INTSTAT)
    #define To_Pi_INTSTAT            (* (reg8 *) To_Pi__INTSTAT)
    #define To_Pi_SNAP               (* (reg8 *) To_Pi__SNAP)
    
	#define To_Pi_0_INTTYPE_REG 		(* (reg8 *) To_Pi__0__INTTYPE)
#endif /* (To_Pi__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_To_Pi_H */


/* [] END OF FILE */
