/*******************************************************************************
* File Name: Out_Compare.h  
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

#if !defined(CY_PINS_Out_Compare_H) /* Pins Out_Compare_H */
#define CY_PINS_Out_Compare_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Out_Compare_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Out_Compare__PORT == 15 && ((Out_Compare__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Out_Compare_Write(uint8 value);
void    Out_Compare_SetDriveMode(uint8 mode);
uint8   Out_Compare_ReadDataReg(void);
uint8   Out_Compare_Read(void);
void    Out_Compare_SetInterruptMode(uint16 position, uint16 mode);
uint8   Out_Compare_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Out_Compare_SetDriveMode() function.
     *  @{
     */
        #define Out_Compare_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Out_Compare_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Out_Compare_DM_RES_UP          PIN_DM_RES_UP
        #define Out_Compare_DM_RES_DWN         PIN_DM_RES_DWN
        #define Out_Compare_DM_OD_LO           PIN_DM_OD_LO
        #define Out_Compare_DM_OD_HI           PIN_DM_OD_HI
        #define Out_Compare_DM_STRONG          PIN_DM_STRONG
        #define Out_Compare_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Out_Compare_MASK               Out_Compare__MASK
#define Out_Compare_SHIFT              Out_Compare__SHIFT
#define Out_Compare_WIDTH              1u

/* Interrupt constants */
#if defined(Out_Compare__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Out_Compare_SetInterruptMode() function.
     *  @{
     */
        #define Out_Compare_INTR_NONE      (uint16)(0x0000u)
        #define Out_Compare_INTR_RISING    (uint16)(0x0001u)
        #define Out_Compare_INTR_FALLING   (uint16)(0x0002u)
        #define Out_Compare_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Out_Compare_INTR_MASK      (0x01u) 
#endif /* (Out_Compare__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Out_Compare_PS                     (* (reg8 *) Out_Compare__PS)
/* Data Register */
#define Out_Compare_DR                     (* (reg8 *) Out_Compare__DR)
/* Port Number */
#define Out_Compare_PRT_NUM                (* (reg8 *) Out_Compare__PRT) 
/* Connect to Analog Globals */                                                  
#define Out_Compare_AG                     (* (reg8 *) Out_Compare__AG)                       
/* Analog MUX bux enable */
#define Out_Compare_AMUX                   (* (reg8 *) Out_Compare__AMUX) 
/* Bidirectional Enable */                                                        
#define Out_Compare_BIE                    (* (reg8 *) Out_Compare__BIE)
/* Bit-mask for Aliased Register Access */
#define Out_Compare_BIT_MASK               (* (reg8 *) Out_Compare__BIT_MASK)
/* Bypass Enable */
#define Out_Compare_BYP                    (* (reg8 *) Out_Compare__BYP)
/* Port wide control signals */                                                   
#define Out_Compare_CTL                    (* (reg8 *) Out_Compare__CTL)
/* Drive Modes */
#define Out_Compare_DM0                    (* (reg8 *) Out_Compare__DM0) 
#define Out_Compare_DM1                    (* (reg8 *) Out_Compare__DM1)
#define Out_Compare_DM2                    (* (reg8 *) Out_Compare__DM2) 
/* Input Buffer Disable Override */
#define Out_Compare_INP_DIS                (* (reg8 *) Out_Compare__INP_DIS)
/* LCD Common or Segment Drive */
#define Out_Compare_LCD_COM_SEG            (* (reg8 *) Out_Compare__LCD_COM_SEG)
/* Enable Segment LCD */
#define Out_Compare_LCD_EN                 (* (reg8 *) Out_Compare__LCD_EN)
/* Slew Rate Control */
#define Out_Compare_SLW                    (* (reg8 *) Out_Compare__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Out_Compare_PRTDSI__CAPS_SEL       (* (reg8 *) Out_Compare__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Out_Compare_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Out_Compare__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Out_Compare_PRTDSI__OE_SEL0        (* (reg8 *) Out_Compare__PRTDSI__OE_SEL0) 
#define Out_Compare_PRTDSI__OE_SEL1        (* (reg8 *) Out_Compare__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Out_Compare_PRTDSI__OUT_SEL0       (* (reg8 *) Out_Compare__PRTDSI__OUT_SEL0) 
#define Out_Compare_PRTDSI__OUT_SEL1       (* (reg8 *) Out_Compare__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Out_Compare_PRTDSI__SYNC_OUT       (* (reg8 *) Out_Compare__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Out_Compare__SIO_CFG)
    #define Out_Compare_SIO_HYST_EN        (* (reg8 *) Out_Compare__SIO_HYST_EN)
    #define Out_Compare_SIO_REG_HIFREQ     (* (reg8 *) Out_Compare__SIO_REG_HIFREQ)
    #define Out_Compare_SIO_CFG            (* (reg8 *) Out_Compare__SIO_CFG)
    #define Out_Compare_SIO_DIFF           (* (reg8 *) Out_Compare__SIO_DIFF)
#endif /* (Out_Compare__SIO_CFG) */

/* Interrupt Registers */
#if defined(Out_Compare__INTSTAT)
    #define Out_Compare_INTSTAT            (* (reg8 *) Out_Compare__INTSTAT)
    #define Out_Compare_SNAP               (* (reg8 *) Out_Compare__SNAP)
    
	#define Out_Compare_0_INTTYPE_REG 		(* (reg8 *) Out_Compare__0__INTTYPE)
#endif /* (Out_Compare__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Out_Compare_H */


/* [] END OF FILE */
