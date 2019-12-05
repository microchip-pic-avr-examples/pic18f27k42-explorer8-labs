/**
  Explorer 8 Variable Speed Rotate (VSR) Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    VSR.c 

  @Summary
    This is the source file for the VSR lab

  @Description
    This source file contains the code for the VSR lab.
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
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Macro Declaration
 */
#define ADDTL_DELAY         21

/**
  Section: Local Variable Declarations
 */
uint8_t activeLedNum;
uint8_t delay;
uint16_t totalDelay;

/*
                             Application    
 */
void VSR(void){    
    if(labState == NOT_RUNNING){    
        // Begin with D6 high
        LEDs_SetLow();
        LED_D6_SetHigh();
        activeLedNum = 6;
        
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"      VSR       ");              
        labState = RUNNING;                                                     
    }

    if (labState == RUNNING){
        // Use the top 8 MSbs of the ADC result as delay
        ADCC_GetConversion(POT_CHANNEL);
        delay = ADCC_GetConversionResult() >> 4;

        // Compute for the total delay [1ms per delay value + 5ms add'l delay + approx. 16ms for the other operations (e.g. LCD)]
        totalDelay = delay + ADDTL_DELAY;
        
        __delay_ms(5);            

        // Decrement the 8 MSbs of the ADC and delay each for 1ms
        while (delay-- != 0){
            __delay_ms(1); 
        }  

        LEDs_ShiftRight();
        activeLedNum++;
        
        // If the last LED (D8) is lit, go back to the first LED (D6)
        if(activeLedNum > 8){
            LED_D6_SetHigh();
            activeLedNum = 6;
        }
        
        // Display the total delay value in ms on the LCD
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)" Delay =     ms ");
        LCD_GoTo(1,9);
        LCD_WriteByte(totalDelay/100+'0');
        LCD_WriteByte((totalDelay/10)%10+'0');
        LCD_WriteByte((totalDelay/1)% 10+'0');
    }

    if(switchEvent){
        labState = NOT_RUNNING;  
    }        
}
/**
 End of File
 */