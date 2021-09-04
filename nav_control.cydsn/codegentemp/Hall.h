/*******************************************************************************
* File Name: Hall.h  
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

#if !defined(CY_PINS_Hall_H) /* Pins Hall_H */
#define CY_PINS_Hall_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Hall_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Hall__PORT == 15 && ((Hall__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Hall_Write(uint8 value);
void    Hall_SetDriveMode(uint8 mode);
uint8   Hall_ReadDataReg(void);
uint8   Hall_Read(void);
void    Hall_SetInterruptMode(uint16 position, uint16 mode);
uint8   Hall_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Hall_SetDriveMode() function.
     *  @{
     */
        #define Hall_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Hall_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Hall_DM_RES_UP          PIN_DM_RES_UP
        #define Hall_DM_RES_DWN         PIN_DM_RES_DWN
        #define Hall_DM_OD_LO           PIN_DM_OD_LO
        #define Hall_DM_OD_HI           PIN_DM_OD_HI
        #define Hall_DM_STRONG          PIN_DM_STRONG
        #define Hall_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Hall_MASK               Hall__MASK
#define Hall_SHIFT              Hall__SHIFT
#define Hall_WIDTH              1u

/* Interrupt constants */
#if defined(Hall__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Hall_SetInterruptMode() function.
     *  @{
     */
        #define Hall_INTR_NONE      (uint16)(0x0000u)
        #define Hall_INTR_RISING    (uint16)(0x0001u)
        #define Hall_INTR_FALLING   (uint16)(0x0002u)
        #define Hall_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Hall_INTR_MASK      (0x01u) 
#endif /* (Hall__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Hall_PS                     (* (reg8 *) Hall__PS)
/* Data Register */
#define Hall_DR                     (* (reg8 *) Hall__DR)
/* Port Number */
#define Hall_PRT_NUM                (* (reg8 *) Hall__PRT) 
/* Connect to Analog Globals */                                                  
#define Hall_AG                     (* (reg8 *) Hall__AG)                       
/* Analog MUX bux enable */
#define Hall_AMUX                   (* (reg8 *) Hall__AMUX) 
/* Bidirectional Enable */                                                        
#define Hall_BIE                    (* (reg8 *) Hall__BIE)
/* Bit-mask for Aliased Register Access */
#define Hall_BIT_MASK               (* (reg8 *) Hall__BIT_MASK)
/* Bypass Enable */
#define Hall_BYP                    (* (reg8 *) Hall__BYP)
/* Port wide control signals */                                                   
#define Hall_CTL                    (* (reg8 *) Hall__CTL)
/* Drive Modes */
#define Hall_DM0                    (* (reg8 *) Hall__DM0) 
#define Hall_DM1                    (* (reg8 *) Hall__DM1)
#define Hall_DM2                    (* (reg8 *) Hall__DM2) 
/* Input Buffer Disable Override */
#define Hall_INP_DIS                (* (reg8 *) Hall__INP_DIS)
/* LCD Common or Segment Drive */
#define Hall_LCD_COM_SEG            (* (reg8 *) Hall__LCD_COM_SEG)
/* Enable Segment LCD */
#define Hall_LCD_EN                 (* (reg8 *) Hall__LCD_EN)
/* Slew Rate Control */
#define Hall_SLW                    (* (reg8 *) Hall__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Hall_PRTDSI__CAPS_SEL       (* (reg8 *) Hall__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Hall_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Hall__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Hall_PRTDSI__OE_SEL0        (* (reg8 *) Hall__PRTDSI__OE_SEL0) 
#define Hall_PRTDSI__OE_SEL1        (* (reg8 *) Hall__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Hall_PRTDSI__OUT_SEL0       (* (reg8 *) Hall__PRTDSI__OUT_SEL0) 
#define Hall_PRTDSI__OUT_SEL1       (* (reg8 *) Hall__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Hall_PRTDSI__SYNC_OUT       (* (reg8 *) Hall__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Hall__SIO_CFG)
    #define Hall_SIO_HYST_EN        (* (reg8 *) Hall__SIO_HYST_EN)
    #define Hall_SIO_REG_HIFREQ     (* (reg8 *) Hall__SIO_REG_HIFREQ)
    #define Hall_SIO_CFG            (* (reg8 *) Hall__SIO_CFG)
    #define Hall_SIO_DIFF           (* (reg8 *) Hall__SIO_DIFF)
#endif /* (Hall__SIO_CFG) */

/* Interrupt Registers */
#if defined(Hall__INTSTAT)
    #define Hall_INTSTAT            (* (reg8 *) Hall__INTSTAT)
    #define Hall_SNAP               (* (reg8 *) Hall__SNAP)
    
	#define Hall_0_INTTYPE_REG 		(* (reg8 *) Hall__0__INTTYPE)
#endif /* (Hall__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Hall_H */


/* [] END OF FILE */
