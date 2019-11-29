/**
  Explorer 8 LCD Header File

  @Company
    Microchip Technology Inc.

  @File Name
    lcd.h

  @Summary
    This is the LCD header file for the Explorer 8 Demo.

  @Description
    This header file provides APIs for the Explorer 8 LCD.
        Device                  :  PIC18F27K42
        Driver Version          :  2.00
        Compiler                :  XC8 1.45
        MPLAB                   :  MPLAB X 4.15
        MPLAB Code Configurator :  MCC 3.45
 */

/*
    (c) 2017 Microchip Technology Inc. and its subsidiaries. You may use this
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


#ifndef LCD_H
#define	LCD_H

/**
  Section: Included Files
 */
#include <stdint.h>

/**
  Section: Macro Declarations
 */
#define IO_EXPD_ADDRESS     0x40  
#define GPIO_A_ADDRESS      0x12
#define GPIO_B_ADDRESS      0x13
#define IO_DIR_A_ADDRESS    0x00
#define IO_DIR_B_ADDRESS    0x01

/**
  Section: Explorer 8 LCD Function Prototypes
 */
void LCD_Initialize(void);
void LCD_WriteIOExpander(uint8_t reg, uint8_t data);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteByte(uint8_t data);
void LCD_WriteString(const uint8_t *data);
void LCD_GoTo(uint8_t row, uint8_t column);
void LCD_Clear(void);

#endif	/* LCD_H */
