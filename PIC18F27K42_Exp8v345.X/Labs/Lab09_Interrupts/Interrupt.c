/**
  Explorer 8 Interrupt Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    Interrupt.c 

  @Summary
    This is the source file for the Interrupt lab

  @Description
    This source file contains the code for the Interrupt lab.
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
#include "../../mcc_generated_files/interrupt_manager.h"
#include "../../mcc_generated_files/tmr0.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Local Function Prototypes
 */
void Lab_Timer0_ISR(void);
void Lab_IOC_ISR(void);

/**
  Section: Local Variable Declaration
 */
uint8_t rotateDirection;
uint8_t rotateCounter;

/*
                             Application    
 */
void Interrupt(void){   
    if(labState == NOT_RUNNING){  
        LEDs_SetLow();
        LED_D6_SetHigh(); 
        
        INTERRUPT_GlobalInterruptEnable();

        INTERRUPT_InterruptOnChangeEnable();
        INTERRUPT_IOCPositiveEnable();
        INTERRUPT_TMR0InterruptEnable();
        
        TMR0_SetInterruptHandler(Lab_Timer0_ISR);
        IOCBF0_SetInterruptHandler(Lab_IOC_ISR); 
        
        rotateDirection = RIGHT;
        rotateCounter = 6;
        
        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)"   Interrupt    "); 
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"Direction: Right"); 
        
        labState = RUNNING;                                                     
    }
    
    if(labState == RUNNING){ 
        // Do nothing. Just wait for an interrupt event 
    }
    
    if(switchEvent){
        INTERRUPT_TMR0InterruptDisable();
        INTERRUPT_InterruptOnChangeDisable();
        INTERRUPT_IOCPositiveDisable();
        
        INTERRUPT_GlobalInterruptDisable();

        labState = NOT_RUNNING;  
    }
}

void Lab_Timer0_ISR(void){
    if(rotateDirection == RIGHT){
        LEDs_ShiftRight();
        rotateCounter++;
        if(rotateCounter > 8){
            LED_D6_SetHigh();
            rotateCounter = 6;
        }
    }else if(rotateDirection == LEFT){
        LEDs_ShiftLeft();
        rotateCounter--;
        if(rotateCounter < 6){
            LED_D8_SetHigh();
            rotateCounter = 8;
        }   
    }
}

void Lab_IOC_ISR(void){
    rotateDirection ^= 1;
    if(rotateDirection == RIGHT){
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"Direction: Right"); 
    }else if(rotateDirection == LEFT){
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"Direction: Left ");
    }
}

/**
 End of File
 */

