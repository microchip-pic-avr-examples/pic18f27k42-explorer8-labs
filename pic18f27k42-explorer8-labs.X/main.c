/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC18F27K42
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 

    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "labs.h"
#include "lcd.h"

/**
  Section: Macro Declarations
 */
#define SWITCH_S1_TTL()    do { INLVLBbits.INLVLB0 =0; } while(0) 
 
void checkButtonS2(void);
void nextLab(void);

/*
                         Main application
 */
void main(void) {
    SYSTEM_Initialize();
    LCD_Initialize();
    SWITCH_S1_TTL();
    
    // Disable the pre-enabled interrupts of the MCC    
    INTERRUPT_TMR0InterruptDisable();
    INTERRUPT_InterruptOnChangeDisable();
    INTERRUPT_IOCPositiveDisable();
    
    LCD_GoTo(0,0);
    LCD_WriteString((const uint8_t *)"    Welcome     ");
    LCD_GoTo(1,0);
    LCD_WriteString((const uint8_t *)"  to Explorer 8 ");
    
    while (1){
        checkButtonS2();
        switch(labNumber){
            case 1:     HelloWorld();       break;
            case 2:     Blink();            break;
            case 3:     Rotate();           break;
            case 4:     ADC();              break;
            case 5:     VSR();              break;
            case 6:     Debounce();         break;
            case 7:     PWM();              break;
            case 8:     Timer1();           break;
            case 9:     Interrupt();        break;
            case 10:    SleepWakeUp();      break;
            case 11:    EEPROM();           break;
        }
        
        if (switchEvent) {
            nextLab();
        }                                                   
    }
}

void checkButtonS2(void){
    if(btnState == NOT_PRESSED){
        if(SWITCH_S2_PORT == LOW){  
            __delay_ms(100);
            btnState = PRESSED;
        }
    }else if(SWITCH_S2_PORT == HIGH){
            btnState = NOT_PRESSED;   
            switchEvent = 1;                                                   
    }
}

void nextLab(void) {
    switchEvent = 0; 
    labNumber++;                                                        

    if (labNumber > 11) {
        labNumber = 1;
    }
}
/**
 End of File
*/