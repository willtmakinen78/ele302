#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef NAV_CONTROL_H
#define NAV_CONTROL_H


float kp_servo; // Proportional constant 
float ki_servo; // Integral constant 
float kd_servo; 
float prev_error_servo; // Error calculated during previous interrupt
float prev_i_term_servo;
int STEER_STATE;
int CENTER_ANGLE;
int RUN_STATE;

void print_xbee(char *string, int num);

CY_ISR(Line_Int_ISR);

CY_ISR(Porch_Int_ISR); 

uint16 Servo_PWM_AngleCalc(int angle);

CY_ISR(V_Sync_ISR); 

CY_ISR(H_Sync_ISR);
#endif

/* [] END OF FILE */
