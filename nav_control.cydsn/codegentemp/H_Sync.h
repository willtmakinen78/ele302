/*******************************************************************************
* File Name: H_Sync.h  
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

#if !defined(CY_PINS_H_Sync_H) /* Pins H_Sync_H */
#define CY_PINS_H_Sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "H_Sync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 H_Sync__PORT == 15 && ((H_Sync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    H_Sync_Write(uint8 value);
void    H_Sync_SetDriveMode(uint8 mode);
uint8   H_Sync_ReadDataReg(void);
uint8   H_Sync_Read(void);
void    H_Sync_SetInterruptMode(uint16 position, uint16 mode);
uint8   H_Sync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the H_Sync_SetDriveMode() function.
     *  @{
     */
        #define H_Sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define H_Sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define H_Sync_DM_RES_UP          PIN_DM_RES_UP
        #define H_Sync_DM_RES_DWN         PIN_DM_RES_DWN
        #define H_Sync_DM_OD_LO           PIN_DM_OD_LO
        #define H_Sync_DM_OD_HI           PIN_DM_OD_HI
        #define H_Sync_DM_STRONG          PIN_DM_STRONG
        #define H_Sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define H_Sync_MASK               H_Sync__MASK
#define H_Sync_SHIFT              H_Sync__SHIFT
#define H_Sync_WIDTH              1u

/* Interrupt constants */
#if defined(H_Sync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in H_Sync_SetInterruptMode() function.
     *  @{
     */
        #define H_Sync_INTR_NONE      (uint16)(0x0000u)
        #define H_Sync_INTR_RISING    (uint16)(0x0001u)
        #define H_Sync_INTR_FALLING   (uint16)(0x0002u)
        #define H_Sync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define H_Sync_INTR_MASK      (0x01u) 
#endif /* (H_Sync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define H_Sync_PS                     (* (reg8 *) H_Sync__PS)
/* Data Register */
#define H_Sync_DR                     (* (reg8 *) H_Sync__DR)
/* Port Number */
#define H_Sync_PRT_NUM                (* (reg8 *) H_Sync__PRT) 
/* Connect to Analog Globals */                                                  
#define H_Sync_AG                     (* (reg8 *) H_Sync__AG)                       
/* Analog MUX bux enable */
#define H_Sync_AMUX                   (* (reg8 *) H_Sync__AMUX) 
/* Bidirectional Enable */                                                        
#define H_Sync_BIE                    (* (reg8 *) H_Sync__BIE)
/* Bit-mask for Aliased Register Access */
#define H_Sync_BIT_MASK               (* (reg8 *) H_Sync__BIT_MASK)
/* Bypass Enable */
#define H_Sync_BYP                    (* (reg8 *) H_Sync__BYP)
/* Port wide control signals */                                                   
#define H_Sync_CTL                    (* (reg8 *) H_Sync__CTL)
/* Drive Modes */
#define H_Sync_DM0                    (* (reg8 *) H_Sync__DM0) 
#define H_Sync_DM1                    (* (reg8 *) H_Sync__DM1)
#define H_Sync_DM2                    (* (reg8 *) H_Sync__DM2) 
/* Input Buffer Disable Override */
#define H_Sync_INP_DIS                (* (reg8 *) H_Sync__INP_DIS)
/* LCD Common or Segment Drive */
#define H_Sync_LCD_COM_SEG            (* (reg8 *) H_Sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define H_Sync_LCD_EN                 (* (reg8 *) H_Sync__LCD_EN)
/* Slew Rate Control */
#define H_Sync_SLW                    (* (reg8 *) H_Sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define H_Sync_PRTDSI__CAPS_SEL       (* (reg8 *) H_Sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define H_Sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) H_Sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define H_Sync_PRTDSI__OE_SEL0        (* (reg8 *) H_Sync__PRTDSI__OE_SEL0) 
#define H_Sync_PRTDSI__OE_SEL1        (* (reg8 *) H_Sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define H_Sync_PRTDSI__OUT_SEL0       (* (reg8 *) H_Sync__PRTDSI__OUT_SEL0) 
#define H_Sync_PRTDSI__OUT_SEL1       (* (reg8 *) H_Sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define H_Sync_PRTDSI__SYNC_OUT       (* (reg8 *) H_Sync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(H_Sync__SIO_CFG)
    #define H_Sync_SIO_HYST_EN        (* (reg8 *) H_Sync__SIO_HYST_EN)
    #define H_Sync_SIO_REG_HIFREQ     (* (reg8 *) H_Sync__SIO_REG_HIFREQ)
    #define H_Sync_SIO_CFG            (* (reg8 *) H_Sync__SIO_CFG)
    #define H_Sync_SIO_DIFF           (* (reg8 *) H_Sync__SIO_DIFF)
#endif /* (H_Sync__SIO_CFG) */

/* Interrupt Registers */
#if defined(H_Sync__INTSTAT)
    #define H_Sync_INTSTAT            (* (reg8 *) H_Sync__INTSTAT)
    #define H_Sync_SNAP               (* (reg8 *) H_Sync__SNAP)
    
	#define H_Sync_0_INTTYPE_REG 		(* (reg8 *) H_Sync__0__INTTYPE)
#endif /* (H_Sync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_H_Sync_H */


/* [] END OF FILE */
