
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cyapicallbacks.h"
#include "math.h"
#include "balloon.h"


#define BUF_SIZE 64 // For writing 
#define MIN_ANGLE 0 // minimum angle
#define MAX_ANGLE 180 // maximum angle
#define MIN_SERVO_PWM 1310 // minimum servo pwm
#define MAX_SERVO_PWM 2620 // maximum servo pwm
#define LEFT_POSITION 0 // smallest angle servos can tolerate 
#define RIGHT_POSITION 150 // largest angle servos can tolerate 

#define FRAME_HEIGHT 240 // max number of rows in frame
#define FRAME_WIDTH 320 // max number of columns in frame
#define MAX_H_PULSES 9 // number of h pulses to wait for until in frame
#define V_SYNC_WAIT 0 // state name for v sync waiting
#define FRAME_WAIT 1 // state name for frame waiting
#define IN_FRAME 2 // state name for being in frame
#define BLACK_THRESHOLD 600 // pixel intensity for black
#define MAX_SAMPLES 10 // number of previous bits to consider for average 
#define LEFT 0 // left of line state when exploring line
#define ON_LINE 1 // on black line state when exploring line
#define RIGHT 2 // right of line state when exploring line 
#define LINE_OF_INTEREST 120 // line that we want to calculate line value for
#define TARGET_LINECOUNT 65060 // ideal line count for line in center
#define NANO_S_PER_COUNT 42 // how many ns elapse per count

// Global flags
int STEER_STATE = 0;
int VIDEO_STATE = 0;
int CAPTURE_FRAME = 0;
int LINE_STATE = LEFT;
int NAVIGATION_LINE = 0;
int CENTER_ANGLE = 74; // true straight angle of servos
int LINE_SEEN = 0;
int FRAME_PARITY = 1;

// Global variables 
int num_h_pulse = 0;
int line_count = 0;
int left_count = 0;
int right_count = 0;
int oldest_value = 0;
int num_interupts = 0;
int average_buf[MAX_SAMPLES];
float average_position;
char outputBuf[BUF_SIZE];
int frameVal[15000];
int frameIndex = 0;
uint16 line_time; 
int numFrame = 0;
int RUN_STATE = 0;

float kp_servo = 0.15; // Proportional constant 
float ki_servo = 0; // Integral constant 
float kd_servo = 0; // Derivative constant
float prev_error_servo = 0; // Error calculated during previous interrupt
float prev_i_term_servo = 0; // Integral term calculated during previous interrupt 
float prev_angle = 74;


// ---------------NAVIGATION CONTROL CODE---------------

//Take in an integer angle btwn 0 and 180 and output corresponding pwm width
// Adapted from arduino map function
uint16 Servo_PWM_AngleCalc(int angle) {
    if (angle < LEFT_POSITION) return MIN_SERVO_PWM;
    else if (angle > RIGHT_POSITION) return MAX_SERVO_PWM;
    return ((angle - MIN_ANGLE) * (MAX_SERVO_PWM - MIN_SERVO_PWM) / (MAX_ANGLE - MIN_ANGLE) + MIN_SERVO_PWM);
}

// Print a string to the XBEE with some formating 
void print_xbee(char* string, int num) {
    char buf[64];
    sprintf(buf, string, num);
    XBEE_PutString(buf);
}

// Control function for steering 
float Servo_PID_Control(float linecount) {
        float p_term = 0;
        float i_term = 0;
        float d_term = 0;
        float output;
       
    
        float error = TARGET_LINECOUNT - linecount;
        
        float dt = 1/30;

        //Proportional Term
        p_term = kp_servo * error;
        //Integral Term
        i_term =  ((ki_servo) * (prev_i_term_servo + (error)*(dt)));
        //Derivative Term
        d_term = kd_servo * ((error - prev_error_servo)/dt);
      
        output = p_term; 
       
        
        prev_error_servo = error;
        prev_i_term_servo = i_term;
        
        return output;
}

// Reset the timer after seeing the back porch
CY_ISR(Porch_Int_ISR) {
    if (line_count == LINE_OF_INTEREST) {
        Line_Time_Reset_Write(1);
        Line_Time_Reset_Write(0);
    }
}

// If on line of interest, calculate error and send PWM value to servo
CY_ISR(Line_Int_ISR){
    float angle;
    float output;
    if (RUN_STATE || STEER_STATE) {
        if (line_count == LINE_OF_INTEREST) {
            LINE_SEEN = 1;
            line_time = Line_Timer_ReadCapture();

            // Determine PWM value to send to Servo
            output = Servo_PID_Control(line_time);
            angle = CENTER_ANGLE  + output;
            
            // Throw out line if too extreme
            if (abs((int)angle - (int)prev_angle) > 150) {
                print_xbee("!!!CALCULATED ANGLE was : %i\n\r", (int)angle);
                angle = prev_angle;
            }
            print_xbee("ANGLE: %i\n\r", (int)angle);
            
            // Write to Servo
            Servo_PWM_WriteCompare(Servo_PWM_AngleCalc((int)angle));
            prev_angle = angle;
        }
    }
}


// V Sync Interrupt Handler
CY_ISR(V_Sync_ISR) {
    VIDEO_STATE = FRAME_WAIT;
}

// H Sync Interrupt Handler
CY_ISR(H_Sync_ISR) {
    num_h_pulse++;
    
    switch(VIDEO_STATE) {
    
        // Waiting for V Sync
        case V_SYNC_WAIT:
            break;
        
        // Waiting for next frame to start
        case FRAME_WAIT:
            num_h_pulse++;
            if (num_h_pulse >= MAX_H_PULSES) {
                num_h_pulse = 0;
                VIDEO_STATE = IN_FRAME;
            }
            break;
            
        // In frame
        case IN_FRAME:  
            
            line_count++;
            // Check if on line of interest
            if (line_count == LINE_OF_INTEREST) {
                NAVIGATION_LINE = 1;
            }
            else {
                NAVIGATION_LINE = 0;  
            }
            
            // Check if end of frame
            if (line_count >= FRAME_HEIGHT) {
                line_count = 0;
                LINE_SEEN = 0;
                VIDEO_STATE = V_SYNC_WAIT;
                FRAME_PARITY = !FRAME_PARITY;
            }
            break; 
    }
}


// ---------------NAVIGATION CONTROL CODE END---------------
/* [] END OF FILE */