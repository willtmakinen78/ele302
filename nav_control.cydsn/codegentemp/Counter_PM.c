/*******************************************************************************
* File Name: Counter_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Counter.h"

static Counter_backupStruct Counter_backup;


/*******************************************************************************
* Function Name: Counter_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Counter_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Counter_SaveConfig(void) 
{
    #if (!Counter_UsingFixedFunction)
        Counter_backup.TimerUdb = Counter_ReadCounter();
        Counter_backup.InterruptMaskValue = Counter_STATUS_MASK;
        #if (Counter_UsingHWCaptureCounter)
            Counter_backup.TimerCaptureCounter = Counter_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Counter_UDB_CONTROL_REG_REMOVED)
            Counter_backup.TimerControlRegister = Counter_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Counter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Counter_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_RestoreConfig(void) 
{   
    #if (!Counter_UsingFixedFunction)

        Counter_WriteCounter(Counter_backup.TimerUdb);
        Counter_STATUS_MASK =Counter_backup.InterruptMaskValue;
        #if (Counter_UsingHWCaptureCounter)
            Counter_SetCaptureCount(Counter_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Counter_UDB_CONTROL_REG_REMOVED)
            Counter_WriteControlRegister(Counter_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Counter_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Counter_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_Sleep(void) 
{
    #if(!Counter_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Counter_CTRL_ENABLE == (Counter_CONTROL & Counter_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Counter_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Counter_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Counter_Stop();
    Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Counter_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Wakeup(void) 
{
    Counter_RestoreConfig();
    #if(!Counter_UDB_CONTROL_REG_REMOVED)
        if(Counter_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Counter_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
