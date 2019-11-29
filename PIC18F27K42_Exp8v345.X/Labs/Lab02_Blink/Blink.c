/**
  Explorer 8 Blink Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    Blink.c 

  @Summary
    This is the source file for the Blink lab

  @Description
    This source file contains the code for the Blink lab.
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
#include "../../mcc_generated_files/tmr1.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Macro Declaration
 */
#define FLAG_COUNTER_MAX 6  // Maximum flag count to create 1.5 seconds delay

/**
  Section: Variable Declaration
 */
uint8_t flagCounter = 0;

/*
                             Application    
 */
void Blink(void){    
    if(labState == NOT_RUNNING){
        LEDs_SetLow(); 
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"     Blink      ");         
        TMR1_StartTimer();  
        labState = RUNNING;                                                    
    }

    if(labState == RUNNING){
        if (LED_D8_PORT == HIGH){
            LCD_GoTo(1,0);
            LCD_WriteString((const uint8_t *)"  LED_D8 = ON   ");   
        }else{
            LCD_GoTo(1,0);
            LCD_WriteString((const uint8_t *)"  LED_D8 = OFF   ");
        }

        while(!TMR1_HasOverflowOccured());   
        TMR1IF = 0;  
        TMR1_Reload();    
        flagCounter++;
        
        if(flagCounter == FLAG_COUNTER_MAX){       
            LED_D8_Toggle();    
            flagCounter = 0;
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