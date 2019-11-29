/**
  Explorer 8 Timer 1 Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    Timer1.c 

  @Summary
    This is the source file for the Timer1 lab

  @Description
    This source file contains the code for the Timer1 lab.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F27K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. You may use this
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
#include "../../mcc_generated_files/tmr1.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Macro Declarations
 */
#define FLAG_COUNTER_MAX    2       // 0.5 seconds delay
#define SHIFT_COUNTER_MAX   2       // 1 second delay
#define TIME_COUNT_MIN      0       // seconds
#define TIME_COUNT_MAX      100     // seconds

/**
  Section: Local Variable Declarations
 */
uint8_t flagCounter;
uint8_t timeCount;
uint8_t shiftCounter;
uint8_t activeLedNum; 

/*
                             Application    
 */
void Timer1(void){
    if(labState == NOT_RUNNING){  
        // Begin with D6 high
        LEDs_SetLow();
        LED_D6_SetHigh();
        activeLedNum = 6;
        
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"    Timer 1    ");   
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"  Start Timer   ");
        
        flagCounter = 0;
        timeCount = 0;
        shiftCounter = 0;
        
        __delay_ms(2000);
        TMR1_StartTimer();              
        labState = RUNNING; 
    }

    if(labState == RUNNING){
        while(!TMR1_HasOverflowOccured());       
        TMR1IF = 0;                
        TMR1_Reload();
        flagCounter++;
        
        // If the second overflow occurs (0.5s delay)
        if(flagCounter == FLAG_COUNTER_MAX){
            LEDs_ShiftRight();
            activeLedNum++;
            
            // If the last LED (D8) is lit, go back to the first LED (D6)
            if(activeLedNum > 8){
                LED_D6_SetHigh();
                activeLedNum = 6;
            }
            
            flagCounter = 0;
            shiftCounter++;
        } 
        
        if(shiftCounter == SHIFT_COUNTER_MAX){
            // Display the time count on the LCD
            LCD_GoTo(1,0);
            LCD_WriteString((const uint8_t *)"Time =     secs ");
            LCD_GoTo(1,7);
            LCD_WriteByte(timeCount/100+'0');
            LCD_WriteByte((timeCount/10)%10+'0');
            LCD_WriteByte((timeCount/1)% 10+'0');
            
            shiftCounter = 0;
            timeCount++;
        }
        
        if (timeCount > TIME_COUNT_MAX){
            timeCount = TIME_COUNT_MIN;
        }                              
    }

    if(switchEvent){   
        TMR1_StopTimer(); 
        labState = NOT_RUNNING;     
    }
}
/**
 End of File
 */