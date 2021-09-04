/*******************************************************************************
* File Name: Arduino_UARTINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Arduino_UART.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Arduino_UART_RX_INTERRUPT_ENABLED && (Arduino_UART_RX_ENABLED || Arduino_UART_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Arduino_UART_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Arduino_UART_rxBuffer - RAM buffer pointer for save received data.
    *  Arduino_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Arduino_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Arduino_UART_rxBufferOverflow - software overflow flag. Set to one
    *     when Arduino_UART_rxBufferWrite index overtakes
    *     Arduino_UART_rxBufferRead index.
    *  Arduino_UART_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Arduino_UART_rxBufferWrite is equal to
    *    Arduino_UART_rxBufferRead
    *  Arduino_UART_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Arduino_UART_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Arduino_UART_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Arduino_UART_RXISR_ENTRY_CALLBACK
        Arduino_UART_RXISR_EntryCallback();
    #endif /* Arduino_UART_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Arduino_UART_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = Arduino_UART_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in Arduino_UART_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (Arduino_UART_RX_STS_BREAK | 
                            Arduino_UART_RX_STS_PAR_ERROR |
                            Arduino_UART_RX_STS_STOP_ERROR | 
                            Arduino_UART_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                Arduino_UART_errorStatus |= readStatus & ( Arduino_UART_RX_STS_BREAK | 
                                                            Arduino_UART_RX_STS_PAR_ERROR | 
                                                            Arduino_UART_RX_STS_STOP_ERROR | 
                                                            Arduino_UART_RX_STS_OVERRUN);
                /* `#START Arduino_UART_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef Arduino_UART_RXISR_ERROR_CALLBACK
                Arduino_UART_RXISR_ERROR_Callback();
            #endif /* Arduino_UART_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & Arduino_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = Arduino_UART_RXDATA_REG;
            #if (Arduino_UART_RXHW_ADDRESS_ENABLED)
                if(Arduino_UART_rxAddressMode == (uint8)Arduino_UART__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & Arduino_UART_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & Arduino_UART_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Arduino_UART_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Arduino_UART_rxAddressDetected = 0u;
                        }
                    }
                    if(Arduino_UART_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        Arduino_UART_rxBuffer[Arduino_UART_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    Arduino_UART_rxBuffer[Arduino_UART_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                Arduino_UART_rxBuffer[Arduino_UART_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (Arduino_UART_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(Arduino_UART_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        Arduino_UART_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    Arduino_UART_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(Arduino_UART_rxBufferWrite >= Arduino_UART_RX_BUFFER_SIZE)
                    {
                        Arduino_UART_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(Arduino_UART_rxBufferWrite == Arduino_UART_rxBufferRead)
                    {
                        Arduino_UART_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (Arduino_UART_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            Arduino_UART_RXSTATUS_MASK_REG  &= (uint8)~Arduino_UART_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(Arduino_UART_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (Arduino_UART_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & Arduino_UART_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START Arduino_UART_RXISR_END` */

        /* `#END` */

    #ifdef Arduino_UART_RXISR_EXIT_CALLBACK
        Arduino_UART_RXISR_ExitCallback();
    #endif /* Arduino_UART_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (Arduino_UART_RX_INTERRUPT_ENABLED && (Arduino_UART_RX_ENABLED || Arduino_UART_HD_ENABLED)) */


#if (Arduino_UART_TX_INTERRUPT_ENABLED && Arduino_UART_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Arduino_UART_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Arduino_UART_txBuffer - RAM buffer pointer for transmit data from.
    *  Arduino_UART_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Arduino_UART_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Arduino_UART_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Arduino_UART_TXISR_ENTRY_CALLBACK
        Arduino_UART_TXISR_EntryCallback();
    #endif /* Arduino_UART_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Arduino_UART_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Arduino_UART_txBufferRead != Arduino_UART_txBufferWrite) &&
             ((Arduino_UART_TXSTATUS_REG & Arduino_UART_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Arduino_UART_txBufferRead >= Arduino_UART_TX_BUFFER_SIZE)
            {
                Arduino_UART_txBufferRead = 0u;
            }

            Arduino_UART_TXDATA_REG = Arduino_UART_txBuffer[Arduino_UART_txBufferRead];

            /* Set next pointer */
            Arduino_UART_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Arduino_UART_TXISR_END` */

        /* `#END` */

    #ifdef Arduino_UART_TXISR_EXIT_CALLBACK
        Arduino_UART_TXISR_ExitCallback();
    #endif /* Arduino_UART_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (Arduino_UART_TX_INTERRUPT_ENABLED && Arduino_UART_TX_ENABLED) */


/* [] END OF FILE */
