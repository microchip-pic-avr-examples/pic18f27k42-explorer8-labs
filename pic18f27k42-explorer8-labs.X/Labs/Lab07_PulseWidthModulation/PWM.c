/**
  Explorer 8 Pulse Width Modulation (PWM) Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    PWM.c 

  @Summary
    This is the source file for the PWM lab

  @Description
    This source file contains the code for the PWM lab.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F27K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
 */

#include "../../mcc_generated_files/pin_manager.h"
#include "../../mcc_generated_files/adcc.h"
#include "../../mcc_generated_files/pwm2.h"
#include "../../mcc_generated_files/tmr2.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Local Function Prototypes
 */
void PWM_Output_D8_Enable (void);
void PWM_Output_D8_Disable (void);

/**
  Section: Local Variable Declarations
 */
uint16_t adcResult;    
uint16_t dutyCycle;

/*
                             Application    
 */
void PWM(void){
    if(labState == NOT_RUNNING){   
        LEDs_SetLow(); 
        TMR2_StartTimer();        
        PWM_Output_D8_Enable();
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"      PWM       ");   
        labState = RUNNING;                                                     
    }

    if(labState == RUNNING){
        ADCC_GetConversion(POT_CHANNEL);
        adcResult = ADCC_GetConversionResult() >> 2;
        PWM2_LoadDutyValue(adcResult);
        dutyCycle = (uint16_t)(((4*CCPR2H)*100UL)/(4*(PR2 + 1)));

        // Display the duty cycle on the LCD
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"Duty Cycle =   %");
        LCD_GoTo(1,13);
        LCD_WriteByte((dutyCycle/10)%10+'0');
        LCD_WriteByte((dutyCycle/1)%10+'0');
    }
    
    if(switchEvent){
        PWM_Output_D8_Disable();
        TMR2_StopTimer();   
        labState = NOT_RUNNING;
    }
}

void PWM_Output_D8_Enable (void){
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    // Set D8 as the output of CCP2
    RB3PPS = 0x0A;

    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
}

void PWM_Output_D8_Disable (void){
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    // Set D8 as GPIO pin
    RB3PPS = 0x00;

    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    
    TRISBbits.TRISB3 = 0;
}



/**
 End of File
 */