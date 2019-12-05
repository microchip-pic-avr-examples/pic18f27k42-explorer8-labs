/**
  Explorer 8 ADC Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    ADC.c 

  @Summary
    This is the source file for the ADC lab

  @Description
    This source file contains the code for the ADC lab.
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
  Section: Local Variable Declaration
 */
uint16_t adcResult = 0; // Used to store the result of the ADC

/*
                             Application    
 */
void ADC(void){
    if(labState == NOT_RUNNING){       
        LEDs_SetLow(); 
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"      ADC       ");    
        labState = RUNNING;                                                     
    }

    if(labState == RUNNING){
        // Get the top 3 MSBs and display these on the LEDs
        ADCC_GetConversion(POT_CHANNEL);
        adcResult = ADCC_GetConversionResult() >> 9;
        LEDs = adcResult << 1;
        
        // Display the ADC result on the LCD
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)" ADC Result =   ");
        LCD_GoTo(1,14);
        LCD_WriteByte((adcResult)%10+'0');
    }

    if(switchEvent){
        labState = NOT_RUNNING; 
    }                                                      
}
/**
 End of File
 */