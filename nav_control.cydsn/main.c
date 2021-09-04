/* ========================================
 * Ryan Thorpe and Will Makinen
 * Group Number: 307
 * File Description: main.c serves as the software that runs on the PSoC that handles things like communication with 
 * the XBee, updating the control equation parameters, determining the PWM width, and other behaviors.
 * 
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cyapicallbacks.h"
#include "nav_control.h"
#include "balloon.h"

//Constants
#define BUF_SIZE 64 // For writing 
#define CIRCUMFERENCE_FT 0.6477 // circumference of wheel
#define COUNTER_MAX 65535 // Maximum value of counter
#define MAGNETS_PER_REV 5.0 // number of magnets on wheel
#define MAX_PWM 255 // Max duty cycle of PWM
#define MICRO_S_PER_COUNT 100 // Microseconds of Elapsed time between counter increment 
#define START_PWM 255 // PWM duty cycle to start car
#define STOP_PWM 0 // PWM duty cycle to stop car



//Global variables 
float TARGET_SPEED = 4.0; // Target speed
float kp = 100; // Proportional constant 
float ki = 10; // Integral constant 
float kd = 0; // Derivative constant
float prev_error = 0; // Error calculated during previous interrupt
float prev_i_term = 0; // Integral term calculated during previous interrupt 
float speed = 0; // current speed of the car

int prevPiRunState = 0;
int piRunState = 0;

CY_ISR(Go_Again_Int_ISR){
    // PWM_Motor_WriteCompare(START_PWM);
}

//Calculate PID output based on target speed and control constants
uint8 PID_Control(float speed, uint16 count) {
        float p_term;
        float i_term;
        float d_term;
        float output;
       
    
        float error = TARGET_SPEED - speed;
        
        uint16 dt = count * MICRO_S_PER_COUNT;
        
        //Proportional Term
        p_term = kp * error;
    
        //Integral Term
        i_term =  ((ki/1000) * (prev_i_term + (error)*(dt)));
        
        //Derivative Term
        d_term = kd * ((error - prev_error)/dt);
       
        output = p_term + i_term + d_term;
        
        prev_error = error;
        prev_i_term = i_term;
        
        //Don't let the output exceed the maximum PWM width
        if (output > MAX_PWM) {
            output = MAX_PWM; 
        }
        
        return (uint8)output;
}

//Prepare the LCD screen for printing 
void LCD_Reset(void) {
    LCD_ClearDisplay();
    LCD_Position(0,0);
}

//Interrupt handler for the Hall Sensor 
CY_ISR(inter) {
    uint16 count;
    int elapsed_time_micro_s;
    float elapsed_time_s; 
    char buf[64];
    uint8 pwm_value;
    
    /* Is program running? */
    if ((RUN_STATE == 1) && (piRunState == 0)) {
        //XBEE_PutString("Driving\n\r");
            
        /* Calculate speed and pwm width */
        count = Counter_ReadCapture();
        Counter_Reset_Write(1);
        Counter_Reset_Write(0);
        count = 65535 - count;
        elapsed_time_micro_s = count * MICRO_S_PER_COUNT;
        elapsed_time_s = (float) elapsed_time_micro_s / (float) 1e6;
        speed = (float) CIRCUMFERENCE_FT / (elapsed_time_s * (float) MAGNETS_PER_REV);
        pwm_value = PID_Control(speed, count);
    
        To_Pi_Write(1);
    
    // Only set values if RUN_STATE is 1
    } else {
        pwm_value = 0;
    }
    
    /* Set PWM Value */
    PWM_Motor_WriteCompare(pwm_value);
}

//Update the PID constants by converting read buffer to a float
static float PID_SetVal(char numBuf[], int numIndex, char readBuf[]) {
    
    int bufIndex = 2;
    char readChar = readBuf[bufIndex]; 
    
    while (readChar != '\r') {
        numBuf[numIndex] = readBuf[bufIndex];
        numIndex++;
        bufIndex++;
        readChar = readBuf[bufIndex];
    }

    numBuf[numIndex] = '\0';
    
    return atof(numBuf);
}

//Main method handles setup, new input
int main(void)
{
    // Local variable declarations
    uint8 readChar;
    uint8 readChar_ard;
    char piChar;
    char readBuf[BUF_SIZE];
    char outputBuf[BUF_SIZE];
    uint8 bufIndex = 0;
    int numIndex = 0;
    char numBuf[BUF_SIZE];
    int angle;
    int newRunState = 0; 
    
    // Start Components for Speed Control
    CyGlobalIntEnable; 
    XBEE_Start();
    LCD_Start();
    Hall_Interrupt_Start();
    Hall_Interrupt_SetVector(inter);
    Counter_Start();
    Counter_Interrupt_Start();
    PWM_Motor_Start();
    V_Sync_Int_Start();
    V_Sync_Int_SetVector(V_Sync_ISR);
    H_Sync_Int_Start();
    H_Sync_Int_SetVector(H_Sync_ISR);
    
    
    // Start Components for Navigation
    Servo_PWM_Start();
    Threshold_Comparator_Start();
    Line_Timer_Start();
    Line_Int_Start();
    Line_Int_SetVector(Line_Int_ISR);
    Porch_Int_Start();
    Porch_Int_SetVector(Porch_Int_ISR);
    
    // Start Components for Balloon Bot
    Go_Again_Int_Start();
    Go_Again_Int_SetVector(Go_Again_Int_ISR);

    Servo_PWM_WriteCompare(Servo_PWM_AngleCalc(CENTER_ANGLE));
    
    // Message to show that PSoC is ready to go
    XBEE_PutString("Connection success\n\r");
    LCD_PrintString("Initialized.");
    
    To_Pi_Write(0);
    for(;;)
    {
        /*----------PI HANDLING----------*/
        
        piRunState = From_Pi_Read();
        if (piRunState == 0) {
            if (prevPiRunState == 1) {
                PWM_Motor_WriteCompare(START_PWM);
                prev_error = 0;
                prev_i_term = 0;
                prev_error_servo = 0;
                prev_i_term_servo = 0;
                piRunState = 0;
                Counter_Reset_Write(1);
                Counter_Reset_Write(0);
            }
        }
        prevPiRunState = piRunState;
        /*----------END PI HANDLING----------*/
        
        /*------------------Input Reading------------------*/
        readChar = XBEE_GetChar();
        /* Read a char */
        if (readChar > 0u) {
            
            
            LCD_Reset();
            LCD_PutChar(readChar);
            readBuf[bufIndex] = readChar;
            bufIndex++;
            
            /* Handle ENTER pressed */
            if (readChar == '\r') {
                LCD_Reset();
                LCD_PrintString("Value entered");
                   
                // Switch case to handle different char inputs
                switch (readBuf[0]) {
                    
                    // If t is pressed, change the target speed
                    case 't':
                        if (RUN_STATE == 0) {
                            TARGET_SPEED = PID_SetVal(numBuf, numIndex, readBuf);
                            sprintf(outputBuf, "Target speed set to %i\n\r", (int)TARGET_SPEED);
                            XBEE_PutString(outputBuf);
                        }
                        break;
                   
                    // If g is pressed, start the car
                    case 'g': 
                        To_Pi_Write(1);
                        if (RUN_STATE == 0) {
                            RUN_STATE = 1;
                            STEER_STATE = 1;
                            BALLOON_STATE = 1;
                            LCD_Reset();
                            LCD_PrintString("----GO----");
                            XBEE_PutString("----GO----\n\r");
                            prev_error = 0;
                            prev_i_term = 0;
                            prev_error_servo = 0;
                            prev_i_term_servo = 0;
                            PWM_Motor_WriteCompare(START_PWM);
                            Counter_Reset_Write(1);
                            Counter_Reset_Write(0);
                        }
                        break;
                        
                        
                    // If s is pressed, stop the car 
                    case 's':
                        To_Pi_Write(0);
                        if (RUN_STATE == 1) {
                            RUN_STATE = 0;
                            BALLOON_STATE = 0;
                            LCD_Reset();
                            LCD_PrintString("----STOP----");
                            PWM_Motor_WriteCompare(STOP_PWM);
                            XBEE_PutString("----STOP----\n\r");
                            prev_error = 0;
                            prev_i_term = 0;
                            prev_error_servo = 0;
                            prev_i_term_servo = 0;
                        }
                        break;
                        
                     // If p is pressed, update the proportional constant 
                    case 'p':
                        LCD_Reset();
                        kp = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "kp=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                       
                    // If i is pressed, update the integral constant     
                    case 'i': 
                        LCD_Reset();
                        ki = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "ki=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                    
                    // If d is pressed, update the derivative constant 
                    case 'd': 
                        LCD_Reset();
                        kd = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "kd=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                     
                    // If k is pressed, print out the current constants and target speed    
                    case 'k':
                        LCD_Reset();
                        sprintf(outputBuf, "kp=%i\n\rki=%i\n\rkd=%i\n\rtarget_speed=%i\n\r", (int)kp, (int)ki, (int)kd, (int)TARGET_SPEED);
                        XBEE_PutString(outputBuf);
                        sprintf(outputBuf, "kp_servo=%i\n\rki_servo=%i\n\rkd_servo=%i\n\rcenter_angle=%i\n\r", (int)kp_servo, (int)ki_servo, (int)kd_servo, (int)CENTER_ANGLE);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                        
                    // If a is pressed, turn 90
                    case 'a':
                        angle = (int)PID_SetVal(numBuf, numIndex, readBuf);
                        sprintf(outputBuf, "a=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        Servo_PWM_WriteCompare(Servo_PWM_AngleCalc(angle));
                        break;
                        
                     // If p is pressed, update the proportional constant 
                    case 'r':
                        LCD_Reset();
                        kp_servo = PID_SetVal(numBuf, numIndex, readBuf);
                        sprintf(outputBuf, "servo kp=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                       
                    // If i is pressed, update the integral constant     
                    case 'n': 
                        LCD_Reset();
                        ki_servo = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "servo ki=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                    
                    // If d is pressed, update the derivative constant 
                    case 'e': 
                        LCD_Reset();
                        kd_servo = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "servo kd=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                        
                    // If c is pressed, update the center angle   
                    case 'c':
                        LCD_Reset();
                        CENTER_ANGLE = PID_SetVal(numBuf, numIndex,readBuf);
                        sprintf(outputBuf, "center angle=%s\n\r", numBuf);
                        XBEE_PutString(outputBuf);
                        LCD_PrintString(outputBuf);
                        break;
                       
                    case 'u':
                        STEER_STATE = 0;
                        LCD_Reset();
                        sprintf(outputBuf, "steering stopped lol\n\r");
                        XBEE_PutString(outputBuf);
                        break;
                        
                    
                    // Handle invalid input case
                    default:
                        LCD_Reset();
                        LCD_PrintString("Invalid input.\n\r");
                        XBEE_PutString("Sending data to Pi\n\r");
                        break;
                        
                }
                bufIndex = 0;
            }
            
        }
        
        /* Clear the BUF */
        if (bufIndex == BUF_SIZE) {
            LCD_Reset();
            XBEE_PutString(readBuf);
            LCD_PrintString(readBuf);
            bufIndex = 0;
        }
        /*-------------------------------------------------*/
    }
}

/* [] END OF FILE */
