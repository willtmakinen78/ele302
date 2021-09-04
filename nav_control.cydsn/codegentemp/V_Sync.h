/*******************************************************************************
* File Name: V_Sync.h  
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

#if !defined(CY_PINS_V_Sync_H) /* Pins V_Sync_H */
#define CY_PINS_V_Sync_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_Sync_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 V_Sync__PORT == 15 && ((V_Sync__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    V_Sync_Write(uint8 value);
void    V_Sync_SetDriveMode(uint8 mode);
uint8   V_Sync_ReadDataReg(void);
uint8   V_Sync_Read(void);
void    V_Sync_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_Sync_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the V_Sync_SetDriveMode() function.
     *  @{
     */
        #define V_Sync_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define V_Sync_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define V_Sync_DM_RES_UP          PIN_DM_RES_UP
        #define V_Sync_DM_RES_DWN         PIN_DM_RES_DWN
        #define V_Sync_DM_OD_LO           PIN_DM_OD_LO
        #define V_Sync_DM_OD_HI           PIN_DM_OD_HI
        #define V_Sync_DM_STRONG          PIN_DM_STRONG
        #define V_Sync_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define V_Sync_MASK               V_Sync__MASK
#define V_Sync_SHIFT              V_Sync__SHIFT
#define V_Sync_WIDTH              1u

/* Interrupt constants */
#if defined(V_Sync__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_Sync_SetInterruptMode() function.
     *  @{
     */
        #define V_Sync_INTR_NONE      (uint16)(0x0000u)
        #define V_Sync_INTR_RISING    (uint16)(0x0001u)
        #define V_Sync_INTR_FALLING   (uint16)(0x0002u)
        #define V_Sync_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define V_Sync_INTR_MASK      (0x01u) 
#endif /* (V_Sync__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_Sync_PS                     (* (reg8 *) V_Sync__PS)
/* Data Register */
#define V_Sync_DR                     (* (reg8 *) V_Sync__DR)
/* Port Number */
#define V_Sync_PRT_NUM                (* (reg8 *) V_Sync__PRT) 
/* Connect to Analog Globals */                                                  
#define V_Sync_AG                     (* (reg8 *) V_Sync__AG)                       
/* Analog MUX bux enable */
#define V_Sync_AMUX                   (* (reg8 *) V_Sync__AMUX) 
/* Bidirectional Enable */                                                        
#define V_Sync_BIE                    (* (reg8 *) V_Sync__BIE)
/* Bit-mask for Aliased Register Access */
#define V_Sync_BIT_MASK               (* (reg8 *) V_Sync__BIT_MASK)
/* Bypass Enable */
#define V_Sync_BYP                    (* (reg8 *) V_Sync__BYP)
/* Port wide control signals */                                                   
#define V_Sync_CTL                    (* (reg8 *) V_Sync__CTL)
/* Drive Modes */
#define V_Sync_DM0                    (* (reg8 *) V_Sync__DM0) 
#define V_Sync_DM1                    (* (reg8 *) V_Sync__DM1)
#define V_Sync_DM2                    (* (reg8 *) V_Sync__DM2) 
/* Input Buffer Disable Override */
#define V_Sync_INP_DIS                (* (reg8 *) V_Sync__INP_DIS)
/* LCD Common or Segment Drive */
#define V_Sync_LCD_COM_SEG            (* (reg8 *) V_Sync__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_Sync_LCD_EN                 (* (reg8 *) V_Sync__LCD_EN)
/* Slew Rate Control */
#define V_Sync_SLW                    (* (reg8 *) V_Sync__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_Sync_PRTDSI__CAPS_SEL       (* (reg8 *) V_Sync__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_Sync_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_Sync__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_Sync_PRTDSI__OE_SEL0        (* (reg8 *) V_Sync__PRTDSI__OE_SEL0) 
#define V_Sync_PRTDSI__OE_SEL1        (* (reg8 *) V_Sync__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_Sync_PRTDSI__OUT_SEL0       (* (reg8 *) V_Sync__PRTDSI__OUT_SEL0) 
#define V_Sync_PRTDSI__OUT_SEL1       (* (reg8 *) V_Sync__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_Sync_PRTDSI__SYNC_OUT       (* (reg8 *) V_Sync__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(V_Sync__SIO_CFG)
    #define V_Sync_SIO_HYST_EN        (* (reg8 *) V_Sync__SIO_HYST_EN)
    #define V_Sync_SIO_REG_HIFREQ     (* (reg8 *) V_Sync__SIO_REG_HIFREQ)
    #define V_Sync_SIO_CFG            (* (reg8 *) V_Sync__SIO_CFG)
    #define V_Sync_SIO_DIFF           (* (reg8 *) V_Sync__SIO_DIFF)
#endif /* (V_Sync__SIO_CFG) */

/* Interrupt Registers */
#if defined(V_Sync__INTSTAT)
    #define V_Sync_INTSTAT            (* (reg8 *) V_Sync__INTSTAT)
    #define V_Sync_SNAP               (* (reg8 *) V_Sync__SNAP)
    
	#define V_Sync_0_INTTYPE_REG 		(* (reg8 *) V_Sync__0__INTTYPE)
#endif /* (V_Sync__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_V_Sync_H */


/* [] END OF FILE */
