/**
  Main Header File

  @Company
    Microchip Technology Inc.

  @File Name
    main.h

  @Summary
    This is the header file for the variables declarations and function prototypes

  @Description
    This header file provides all the variables and function prototypes used in this project.
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

#ifndef LABS_H
#define	LABS_H

#include <xc.h>
#include <stdint.h>
    

/**
  Section: Macro Declarations
 */
    #define _XTAL_FREQ          8000000
    #define PRESSED             1
    #define NOT_PRESSED         0
    #define RUNNING             1
    #define NOT_RUNNING         0
    #define RIGHT               1
    #define LEFT                0
    #define LEDs                LATB
    #define LEDs_SetLow()       do { LATB = 0; } while(0)
    #define LEDs_ShiftRight()   do { LATB <<= 1; } while(0)
    #define LEDs_ShiftLeft()    do { LATB >>= 1; } while(0)

    #define INTERRUPT_TMR0InterruptEnable()         do { PIE3bits.TMR0IE = 1; } while(0)
    #define INTERRUPT_InterruptOnChangeEnable()     do { PIE0bits.IOCIE = 1; } while(0)
    #define INTERRUPT_IOCPositiveEnable()           do { IOCBP0 = 1; } while(0)
    #define INTERRUPT_TMR0InterruptDisable()        do { PIE3bits.TMR0IE = 0; } while(0)
    #define INTERRUPT_InterruptOnChangeDisable()    do { PIE0bits.IOCIE = 0; } while(0)
    #define INTERRUPT_IOCPositiveDisable()          do { IOCBP0 = 0; } while(0)


/**
  Section: Variable Definitions
 */
    uint8_t labNumber = 0;
    uint8_t switchEvent = 0;
    uint8_t labState = NOT_RUNNING;
    uint8_t btnState = NOT_PRESSED;    

/**
  Section: Function Prototypes
 */
    
/**
  @Summary
    Performs the HelloWorld Lab.

  @Description
    This turns on LED_D8 on the Explorer8 Board. The LED status is displayed on 
    the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void HelloWorld(void);

/**
  @Summary
    Performs the Blink Lab.

  @Description
    LED_D8 blinks at a rate of approximately 1.5 seconds. The LED status is
    displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void Blink(void);

/**
  @Summary
    Performs the Rotate Lab.

  @Description
    The LEDs rotate from left to right at a rate of 0.5s. The status of the LEDs are
    displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void Rotate(void);

/**
  @Summary
    Performs the Analog to Digital Conversion Lab.

  @Description
    The top 3 MSbs of the ADC are displayed on the LEDs. Rotate the potentiometer 
    to change the display. The same is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void ADC(void);

/**
  @Summary
    Performs the Variable Speed Rotate Lab.

  @Description
    The LEDs rotate from left to right similar to Rotate Lab with varying speed.
    Rotate the POT counterclockwise to see the LEDs shift faster.
    The approximate total delay value is displayed on the LCD. 

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void VSR(void);

/**
  @Summary
    Performs the Debounce Lab.

  @Description
    When SWITCH_S1 is pressed, it will light one LED in the array.
    Pressing it again will light the next LED to the right and so on.
    When the switch is held down, it will show a rotating pattern like Lab 3.
    The LEDs' status is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void Debounce(void);

/**
  @Summary
    Performs the Pulse Width Modulation Lab.

  @Description
    Rotating the potentiometer will adjust the brightness of a single LED, LED_D8. 
    The duty cycle is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void PWM(void);

/**
  @Summary
    Performs the Timer1 Lab.

  @Description
    The LEDs rotate from left to right, similar to Rotate Lab, at a rate of ~0.5 seconds.
    A counter also increments every ~1 second and is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void Timer1(void);

/**
  @Summary
    Performs the Interrupt Lab.

  @Description
    The LEDs rotate at a constant speed and the switch reverses their direction.
    The direction is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void Interrupt(void);

/**
  @Summary
    Performs the Sleep-Wakeup Lab.

  @Description
    LED_D7 is ON while the MCU is in sleep mode. After 8 seconds, the Watchdog 
    Timer will wake up the device from sleep then both LED_D6 and LED_D8 will turn ON, 
    while LED_D7 will turn OFF. The status of the device is displayed on the LCD.

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void SleepWakeUp(void);

/**
  @Summary
    Performs the EEPROM Lab.

  @Description
   Whenever SWITCH_S1 is pressed, the top 3 MSBs of the ADC is written to EEPROM. These are read 
   afterwards and displayed on the LEDs and LCD. Rotating the potentiometer changes value of the 
   ADC to be stored/read to/from EEPROM. 

  @Preconditions
    SYSTEM_Initialize() and LCD_Initialize() functions should have been called before calling this function.

  @Returns
    None

  @Param
    none
*/
void EEPROM(void);

#endif	/* LABS_H */
/**
 End of File
 */