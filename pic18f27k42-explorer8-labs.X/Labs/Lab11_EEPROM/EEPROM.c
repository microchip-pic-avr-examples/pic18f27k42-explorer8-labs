/**
  EEPROM Lab Source File

  Company:
    Microchip Technology Inc.

  File Name:
    EEPROM.c

  Summary:
    This is the source file for the EEPROM lab

  Description:
    This source file contains the code on how the EEPROM lab works.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC18F27K42
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */
#include "../../mcc_generated_files/memory.h"
#include "../../mcc_generated_files/pin_manager.h"
#include "../../mcc_generated_files/adcc.h"
#include "../../mcc_generated_files/interrupt_manager.h"
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Local Function Prototypes
 */
void Lab_EEPROM_ISR(void);

/**
  Section: Macro Declaration
 */
#define EEPROM_ADDR    0x310000    // EEPROM starting address

/**
  Section: Local Variable Declarations
 */
uint16_t adcResult;

/*
                             Application    
 */
void EEPROM(void) {
    if (labState == NOT_RUNNING) {
        LEDs_SetLow();

        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_InterruptOnChangeEnable();
        INTERRUPT_IOCPositiveEnable();

        IOCBF0_SetInterruptHandler(Lab_EEPROM_ISR);

        LCD_GoTo(0, 0);
        LCD_WriteString((const uint8_t *)"     EEPROM        ");

        adcResult = 0;

        labState = RUNNING;
    }

    if (labState == RUNNING) {
        uint8_t readData;
        
        // Display the stored data from the EEPROM onto the LEDs (MSB = LED_D8, LSB = LED_D6)   
        readData = DATAEE_ReadByte(EEPROM_ADDR);
        LEDs = readData << 1;

        // Display the stored data from the EEPROM onto the LCD
        LCD_GoTo(1, 0);
        LCD_WriteString((const uint8_t *)"   Value =     ");
        LCD_GoTo(1, 11);
        LCD_WriteByte((readData) % 10 + '0');
    }

    if (switchEvent) {
        INTERRUPT_TMR0InterruptDisable();
        INTERRUPT_InterruptOnChangeDisable();
        INTERRUPT_IOCPositiveDisable();

        INTERRUPT_GlobalInterruptDisable();

        labState = NOT_RUNNING;
    }

}

void Lab_EEPROM_ISR(void) {
    // Debounce by waiting and seeing if S1 is still held down
    __delay_ms(20);

    // Get the top 3 MSBs and display it in the LEDs
    ADCC_GetConversion(POT_CHANNEL);
    adcResult = ADCC_GetConversionResult() >> 9;

    // Save the value to EEPROM and wait for the next IOC event
    DATAEE_WriteByte(EEPROM_ADDR, adcResult);

}
/**
 End of File
 */