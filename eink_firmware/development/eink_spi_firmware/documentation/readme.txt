Overview
========
'eink_spi_firmware.c' is an implementation for controlling and displaying images on a Waveshare 2.9 inch V2
e-ink module.

The controller is the FRDM-K64F board, and it communicates to the e-ink display via SPI.

Toolchain supported
===================
- MCUXpresso  11.5.0

Hardware requirements
=====================
- Mini/micro USB cable
- FRDM-K64F board
- Waveshare e-Paper Driver Hat
- Waveshare 2.9 e-ink display V2 --> https://www.waveshare.com/wiki/2.9inch_e-Paper_Module
- Wires to connect e-ink display to FRDM-K64F board
- Personal Computer

Board settings
==============
Wiring between FRDM-K64F board and Waveshare 2.9 in V2 e-ink display
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
FRDM Board                              E-INK Display
INSTANCE0(SPI)      CONNECTS TO         INSTANCE1(SPI)
Pin Name   Board Location     			Pin Name  
PORTE26	   J2 pin 1						BUSY
PORTC12    J2 pin 2    					RST
PORTC4     J2 pin 4						D/C    
PORTC3     J1 pin 16					CS      
SCK        J2 pin 12           			CLK
SOUT       J2 pin 8            			DIN     
GND        J3 pin 14               		GND       
3.3V	   J3 pin 4						VCC
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Running the firmware
====================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Controlling the E-INK Display:

Button SW3, next to the RGB LED, controls the e-ink display.

Quick Single Press --> clears screen and displays 1st image
Regular Single Press --> clears screen and displays 2nd image
Two Quick Single Presses --> clears screen and displays 3rd image
Long Single Presses --> clears screen and leaves it blank

 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note about the base code for the Waveshare E-INK Display:

Waveshare provides open source code to integrate their display with STM32-F103ZET6 mcu.
Their is source code is at https://github.com/waveshare/e-Paper/tree/master/STM32/STM32-F103ZET6

I adapted their code so that it utilizes the SPI commands for the FRDM-K64F board.
The relevant source files for the display are 'eink.h' and 'eink.c'.

'eink_spi_firmware.c' also initializes the SW3 button on the FRDM-K64F board.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Note about SysTick_Handler:

Commented out the FreeRTOS SysTick_Handler function so that I can use my own custom handler.
FreeRTOS SysTick_Handler function located in --> 
/eink_spi_firmware/freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.c
To activate it, uncomment the function prototype and function definition.

My custom Systick_Handler is in --> /eink_spi_firmware/source/eink.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~