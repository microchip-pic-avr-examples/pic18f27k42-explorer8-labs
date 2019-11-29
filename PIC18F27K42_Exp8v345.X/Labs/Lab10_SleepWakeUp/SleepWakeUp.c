/**
  Explorer 8 Sleep Wakeup Lab Source File

  @Company
    Microchip Technology Inc.

  @File Name
    SleepWakeup.c 

  @Summary
    This is the source file for the Sleep Wakeup lab

  @Description
    This source file contains the code for the Sleep Wakeup lab.
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
#include "../../labs.h"
#include "../../lcd.h"

/**
  Section: Macro Declaration
 */
#define COUNTDOWN_MAX   5           // seconds
#define WDT_Enable()    (WDTCON0bits.SWDTEN = 1)
#define WDT_Disable()    (WDTCON0bits.SWDTEN = 0)

/**
  Section: Local Function Prototypes
 */
void FSCM_SwitchExternal(uint8_t val);

/*
                             Application    
 */
void SleepWakeUp(void){
    if(labState == NOT_RUNNING){   
        LEDs_SetLow();
        LED_D7_SetHigh();

        LCD_GoTo(0,0);
        LCD_WriteString((const uint8_t *)" Sleep/Wake Up  "); 
        
        WDT_Enable();  
       
        uint8_t wdtTimer = COUNTDOWN_MAX;
        for(uint8_t i = 0; i < COUNTDOWN_MAX; i++){
            LCD_GoTo(1,0);
            LCD_WriteString((const uint8_t *)" Sleeping in    "); 
            LCD_GoTo(1,13);
            LCD_WriteByte((wdtTimer)%10+'0');
            
            wdtTimer--;
            __delay_ms(1000);
        }
        
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)"Wait for 8 secs "); 
        
        // Switch back to external clock after sleeping
        uint8_t tmp = OSCCON1;
        SLEEP();
        FSCM_SwitchExternal(tmp);

        labState = RUNNING;                                                     
    }
      
    if(labState == RUNNING){
        // Wait for 8s for the WDT time-out; and the LEDs will toggle
        LED_D7_LAT = LOW;   
        LED_D6_LAT = LED_D8_LAT = HIGH;  
        
        LCD_GoTo(1,0);
        LCD_WriteString((const uint8_t *)" I'm now awake! "); 
        
        WDT_Disable(); 
    }

    if(switchEvent){
        labState = NOT_RUNNING;
    }           
}

void FSCM_SwitchExternal(uint8_t val) {
    PIR0bits.OSFIF = 0;
    OSCCON1 = val;
}
/**
 End of File
 */