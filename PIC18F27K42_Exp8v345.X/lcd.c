/**
  Explorer 8 LCD Source File

  @Company
    Microchip Technology Inc.

  @File Name
    lcd.c

  @Summary
    This is the source file for the Explorer 8 LCD.

  @Description
    This source file provides implementations for APIs for the Explorer 8 LCD.
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

/**
  Section: Included Files
 */
#include "lcd.h"
#include "mcc_generated_files/mcc.h"

/**
  Section: Macro Declarations
 */
#define LCD_CLEAR               0x01
#define LCD_VDD_EN              0x20
#define LCD_FUNCTION_SET        0x3C
#define LCD_SET_DISPLAY         0x0C
#define LCD_SET_DDRAM_ADDRESS   0x80
#define LINE1_START_ADDRESS     0x80
#define LINE2_START_ADDRESS     0xC0
#define OUTPUT_DIR              0x00

/**
  Section: Explorer 8 LCD APIs
 */
void LCD_Initialize(void) {
    LCD_WriteIOExpander(IO_DIR_A_ADDRESS, OUTPUT_DIR);
    LCD_WriteIOExpander(IO_DIR_B_ADDRESS, OUTPUT_DIR);
    LCD_WriteIOExpander(GPIO_A_ADDRESS, LCD_VDD_EN);
    __delay_ms(10);
    LCD_WriteCommand(LCD_FUNCTION_SET);
    __delay_ms(10);
    LCD_WriteCommand(LCD_SET_DISPLAY);
    __delay_ms(10);
    LCD_WriteCommand(LCD_CLEAR);
    __delay_ms(10);
    LCD_WriteCommand(LCD_SET_DISPLAY);
    __delay_ms(130);
    LCD_WriteCommand(LCD_SET_DDRAM_ADDRESS);
    __delay_ms(1);
}

void LCD_WriteIOExpander(uint8_t reg, uint8_t data) {
    LCD_CHIP_SELECT_SetLow();
    SPI1_Exchange8bit(IO_EXPD_ADDRESS);
    SPI1_Exchange8bit(reg);
    SPI1_Exchange8bit(data);
    LCD_CHIP_SELECT_SetHigh();
}

void LCD_WriteCommand(uint8_t cmd) {
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0x60);  //RS LOW -- E HIGH -- LCD Enabled 
    LCD_WriteIOExpander(GPIO_B_ADDRESS, cmd);   //Write the command on PORT B
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0x20);  //RS LOW -- E LOW -- LCD Enabled
}

void LCD_WriteByte(uint8_t data) {
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0xE0);  //RS HIGH -- E HIGH -- LCD Enabled --> This is to choose the data register on the LCD
    LCD_WriteIOExpander(GPIO_B_ADDRESS, data);  //Write the byte on PORT B
    LCD_WriteIOExpander(GPIO_A_ADDRESS, 0xA0);  //RS HIGH -- E LOW -- LCD enabled --> This is to latch the data on the LCD
}

void LCD_WriteString(const uint8_t *data) {
    uint8_t i = 0;
    while (data[i]) {
        LCD_WriteByte(data[i++]);
    }
}

void LCD_GoTo(uint8_t row, uint8_t column) {
    if (row < 2) {
        uint8_t pos = (row == 0) ? (LINE1_START_ADDRESS | column) : (LINE2_START_ADDRESS | column);
        LCD_WriteCommand(pos);
    }
}

void LCD_Clear(void) {
    LCD_WriteCommand(LCD_CLEAR);
    LCD_GoTo(0, 0);
}
