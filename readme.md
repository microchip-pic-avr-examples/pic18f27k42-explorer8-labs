[![MCHP](https://cldup.com/U0qhLwBijF.png)](https://www.microchip.com) 

# PIC18F27K42 Explorer-8 Labs

# I.Introduction
The goal of this example is to provide 11 labs that will demonstrate Explorer 8 board capabilities and showcase the functionality of PIC18F27K42 device. The concept is to create a state machine where you can navigate through each lab by pressing the S2 button.  Another button(S1) is used to execute labs requiring external stimulus. The output of labs is shown using three LEDs and an LCD provided by the Explorer 8 development board. Some labs need a potentiometer for Analog input. This project is primarily created with the aim of helping beginners in basic programming of MCUs.

This example also make use of the latest MPLAB Code Configurator (MCC v3.75), an easy-to-use plugin tool for MPLAB X IDE(v5.15) that you can use to generate codes for a more efficient use of the CPU and memory resources. All labs are written in C language and are compatible with the latest XC8 compiler (XC8 v2.00).

# II.Tools
## A. Explorer 8 Development Board
![]( https://i.imgur.com/ZHFOx7c.jpg){width=auto height=auto align=center}

## B.Software
a.MPLAB X IDE [(http://www.microchip.com/mplab/mplab-x-ide](http://www.microchip.com/mplab/mplab-x-ide))

b.	MPLAB X Code Configurator [(http://www.microchip.com/mplab/mplab-code-configurator](http://www.microchip.com/mplab/mplab-code-configurator))

c.	XC8 Compilers ([http://www.microchip.com/mplab/compilers](http://www.microchip.com/mplab/compilers)) 


# III. Flow Chart
![]( https://i.imgur.com/zalZL9S.jpg){width=auto height=auto align=center}
# IV.	System Setup
MPLAB Code Configurator (MCC) is used to configure the system setup for the PIC18F27K42. The external clock is used for oscillator and then set to 8 MHz. The watchdog timer is set through SWDTEN with a period of approximately eight seconds.

![]( https://i.imgur.com/0MbVWIi.jpg){width=auto height=auto align=center}

# V.	Lab Descriptions
## Lessons:
### A.	Hello World
This lab shows how to configure, initialize and turn on an I/O (LED_D8) pin while the LCD displays “Hello World” and “LED_D8 = ON” on the first and second line respectively.

### B.	Blink
This lab shows how to create a blinking LED using Timer1. LED_D8, which is OFF at its initial state, toggles every 1.5 seconds creating a blinking sequence. The LCD displays “Blink” on the first line while displaying “LED_D8 = OFF” and “LED_D8 = ON” alternately every 1.5 seconds on the second line. The Timer1 module is used for accurate timing.

![]( https://i.imgur.com/jmeWMba.png){width=auto height=auto align=center}

### C.	Rotate
LEDs D6, D7 and D8 light up in turn every 500 milliseconds software delay. Once D8 is lit, D6 lights up and the pattern repeats. The LCD displays “Rotate” on the first line and “LED_Dx = ON” on the second line, where x indicates which LED is currently lit.  

![]( https://i.imgur.com/ZDGUaNN.png){width=auto height=auto align=center}

### D.	ADC 
This lab shows how to configure the ADC, run a conversion, read the analog voltage controlled by the on-board potentiometer, and display the high order three bits on the LEDs. The LCD displays “ADC” on the first line and “ADC Result = x” on the second line where x shows the current ADC conversion result from 0 (0b000) to 7(0b111).

![](https://i.imgur.com/bZXDLIM.png){width=auto height=auto align=center}

![]( https://i.imgur.com/s7I3pAE.png){width=auto height=auto align=center}

### E.	VSR
This lesson combines all the previous lessons to produce a variable speed rotating LED display. The LEDs rotates from left to right. The Speed of the rotation depends on the ADC value provided by the potentiometer. The LCD displays “VSR” on the first line and “Delay = xxx ms” on the second line, where xxx indicates the time interval between LED shifts.

![](https://i.imgur.com/0qjWG99.png){width=auto height=auto align=center}

### F.           Debounce
LEDs D6, D7 and D8 light up in turn every S1 button press. Once D8 is lit and S1 is pressed, D6 lights up and the pattern repeats. Holding the button moves the light continuously across the LEDs. The LCD displays “Debounce” on the first line and “LED_Dx = ON” on the second line, where x indicates which LED is currently lit.

![]( https://i.imgur.com/zIAtnuL.png){width=auto height=auto align=center}

### G.	PWM
In this lab, rotating the potentiometer changes the light intensity of LED_D8. The value of the ADC provided by the potentiometer changes the value of the duty cycle which determines the brightness of the LED. The LCD displays “PWM” on the first line and “Duty Cycle = xx%” on the second line, where xx corresponds to the PWM duty cycle.

![](https://i.imgur.com/LjDXLzI.png){width=auto height=auto align=center}

![]( https://i.imgur.com/fMcgBfp.png){width=auto height=auto align=center}

![]( https://i.imgur.com/fjucotr.png) {width=auto height=auto align=center}



### H.	Timers
This lab produces the same output as rotate lab the only difference is that it uses Timer1 instead of software delay function. The LCD displays “TIMER1” on the first line and “Time = xxx secs” on the second line where xxx indicates a value between 0 and 100 corresponding to the time since TIMER1 started incrementing. A 1-second increment is equivalent to two LED shifts. When the display reaches 100, it will reset to 0 and the counting goes on.

![]( https://i.imgur.com/zZ1K5qH.png){width=auto height=auto align=center}

![]( https://i.imgur.com/qrXxOiK.png){width=auto height=auto align=center}

### I.	Interrupt
Light on LEDs D6, D7 and D8 shift at a constant speed and pressing switch S1 reverses the direction of rotation. The LCD displays “Interrupt” on the first line and “Direction = x” on the second line, where x can either be “Left” or “Right” depending upon the direction of rotation. Interrupts signal events that require servicing by the software’s Interrupt Service Routine(ISR). It is a more efficient way of watching out for events than continuously polling a register.

![]( https://i.imgur.com/BL3LuJZ.jpg){width=auto height=auto align=center}

![]( https://i.imgur.com/Crck3RE.png){width=auto height=auto align=center}

### J.	Sleep/Wakeup
This lab introduces the Sleep mode function which puts the device into a low power standby mode.  Upon entering this lab, a countdown timer will be displayed on the LCD while LED_D7 is ON and LEDs D6/D8 are OFF and the device will be put into Sleep after 5 seconds. The device will then wake up after 8 seconds, toggling the state of LEDs and the LCD will display “I’m now awake!” on the second line.

![]( https://i.imgur.com/KlYfHCO.png){width=auto height=auto align=center}



### K.	EEPROM
In this lab, the top 3 converted MSB value of the ADC from the potentiometer input is written on the EEPROM whenever S1 button is pressed. The value written on the EEPROM is then read and displayed on the LEDs D6-D8. The LCD displays “EEPROM” on the first line and “Value = x” on the second line, where x corresponds to the saved ADC result in the EEPROM.
	
 ![](https://i.imgur.com/eDhCvYk.png){width=auto height=auto align=center}

![]( https://i.imgur.com/H226nXs.png){width=auto height=auto align=center}


Note:  For the complete step by step guide in making this example, [click here]( http://ww1.microchip.com/downloads/en/DeviceDoc/Explorer8_Labs_v2.zip) and open the Read Me document inside the downloaded folder.

