/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include "nav_control.h"

#define SEARCHING 1
#define FOUND 2
#define TARGETING 3

int BALLOON_STATE = SEARCHING;

/*
CY_ISR (Balloon_Stop_Int_ISR) {
   RUN_STATE = 0;
}

CY_ISR (Balloon_Start_Int_ISR) {
   RUN_STATE = 1;
}
*/

/* [] END OF FILE */
