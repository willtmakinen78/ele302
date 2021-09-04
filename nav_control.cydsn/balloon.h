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

#ifndef BALLOON_H
#define BALLOON_H

int BALLOON_STATE;
int RUN_STATE;

CY_ISR(Balloon_Stop_Int_ISR);
CY_ISR(Balloon_Start_Int_ISR);
/* [] END OF FILE */

#endif