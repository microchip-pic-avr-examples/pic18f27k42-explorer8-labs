/**
  Explorer 8 Debounce Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    Debounce.c 

  @Summary
    This is the source file for the Debounce lab

  @Description
    This source file contains the code for the Debounce lab.
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

#include "../../mcc_generated_files/mcc.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Local Variable Declaration
 */
uint8_t activeLedNum;

/*
                             Application    
 */
void Debounce(void){
    if(labState == NOT_RUNNING){    
        // Begin with D6 high
        LEDs_SetLow();
        LED_D6_SetHigh();
        activeLedNum = 6;
        
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"    Debounce    ");
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"    Press S1    ");          
        labState = RUNNING;                                                     
    }

    if (labState == RUNNING){
        // The Switch is normally tied to VDD ...when it is pressed, the switch port is connected to GND
        if (SWITCH_S1_PORT == LOW){
            // Debounce by delaying
            for(uint8_t i=0; i<6; i++){
                __delay_ms(20);
            }

            // If S1 is still pressed, shift the light to the next LED to the right
            if (SWITCH_S1_PORT == LOW){
                LEDs_ShiftRight();
                activeLedNum++;
                
                // If the last LED (D8) is lit, go back to the first LED (D6)
                if(activeLedNum > 8){
                    LED_D6_SetHigh();
                    activeLedNum = 6;
                }

                // Display which LED is lit to the LCD
                LCD_GoTo(1,0);
                LCD_WriteString((const uint8_t *)"  LED_D  = ON   ");
                LCD_GoTo(1,7);
                LCD_WriteByte(activeLedNum+'0');
            }
        }
    }

    if(switchEvent){
        labState = NOT_RUNNING; 
    }                                            
}
/**
 End of File
 */
