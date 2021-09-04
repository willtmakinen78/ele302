/*******************************************************************************
* File Name: Video_ADC_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Video_ADC.h"


/***************************************
* Local data allocation
***************************************/

static Video_ADC_BACKUP_STRUCT  Video_ADC_backup =
{
    Video_ADC_DISABLED
};


/*******************************************************************************
* Function Name: Video_ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Video_ADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Video_ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Video_ADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: Video_ADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The Video_ADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Video_ADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Video_ADC_Sleep(void)
{
    if((Video_ADC_PWRMGR_SAR_REG  & Video_ADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((Video_ADC_SAR_CSR0_REG & Video_ADC_SAR_SOF_START_CONV) != 0u)
        {
            Video_ADC_backup.enableState = Video_ADC_ENABLED | Video_ADC_STARTED;
        }
        else
        {
            Video_ADC_backup.enableState = Video_ADC_ENABLED;
        }
        Video_ADC_Stop();
    }
    else
    {
        Video_ADC_backup.enableState = Video_ADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: Video_ADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  Video_ADC_Sleep() was called. If the component was enabled before the
*  Video_ADC_Sleep() function was called, the
*  Video_ADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Video_ADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Video_ADC_Wakeup(void)
{
    if(Video_ADC_backup.enableState != Video_ADC_DISABLED)
    {
        Video_ADC_Enable();
        #if(Video_ADC_DEFAULT_CONV_MODE != Video_ADC__HARDWARE_TRIGGER)
            if((Video_ADC_backup.enableState & Video_ADC_STARTED) != 0u)
            {
                Video_ADC_StartConvert();
            }
        #endif /* End Video_ADC_DEFAULT_CONV_MODE != Video_ADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
