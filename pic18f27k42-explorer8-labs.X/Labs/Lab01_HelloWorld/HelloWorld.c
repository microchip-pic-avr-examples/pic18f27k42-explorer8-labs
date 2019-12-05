/**
  Explorer 8 HelloWorld Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    HelloWorld.c 

  @Summary
    This is the source file for the Hello World lab

  @Description
    This source file contains the code for the Hello World lab.
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
#include "../../labs.h"
#include "../../lcd.h"

/*
                             Application    
 */
void HelloWorld(void){
    if(labState == NOT_RUNNING){ 
        LEDs_SetLow();
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"  Hello World   ");       
        labState = RUNNING;                                      
    }

    if(labState == RUNNING){
        LED_D8_SetHigh();
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"  LED_D8 = ON   ");       
    }

    if(switchEvent){
        labState = NOT_RUNNING;   
    }                                              
}
/**
 End of File
 */
