/*
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    eink_spi_FreeRTOS_optional.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_dspi.h"
#include "eink.h"
#include "fsl_component_button.h"
#include "fsl_port.h"
#include "fsl_component_timer_manager.h"
/* TODO: insert other definitions and declarations here. */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PIN4_IDX                  4u   /*!< Pin number for pin 4 in a port */
#define TIMER_SOURCE_CLOCK        CLOCK_GetFreq(kCLOCK_BusClk)

/*! @brief display_state definition */
typedef enum _display_state
{
    kDisplay_DoNothing         = 0U,
	kDisplay_PrintPrimaryImage = 1U,
	kDisplay_PrintSecondImage  = 2U,
	kDisplay_PrintThirdImage   = 3U,
	kDisplay_Clear             = 4U

} display_state_t;


/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile display_state_t display_state;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* Functions for displaying different images. */
void displayPrimaryImage(void);
void displaySecondaryImage(void);
void displayThirdImage(void);

/* Functions for setting up SW3 button of FRDM board. */
void SW3_configure_button(void);
button_status_t button_callback(void *buttonHandle, button_callback_message_t *message, void *callbackParam);

 /*******************************************************************************
  * Functions
  ******************************************************************************/
void displayPrimaryImage(void)
{
	/* Drawing Sequence */
	EINK_Init(); // brings the cursor to top left corner of screen (0,0)
	EINK_Clear(); // clears any image on screen
	EINK_Display(gImage_ian_doge_wallet, IAN_DOGE_WALLET_SIZE); // draw the dogecoin wallet image
}

void displaySecondaryImage(void)
{

	/* Drawing Sequence */
	EINK_Init(); // brings the cursor to top left corner of screen (0,0)
	EINK_Clear(); // clears any image on screen
	EINK_Display(gImage_santi_doge_wallet, SANTI_DOGE_WALLET_SIZE); // draw the dogecoin wallet image

}

void displayThirdImage(void)
{
	/* Drawing Sequence */
	EINK_Init(); // brings the cursor to top left corner of screen (0,0)
	EINK_Clear(); // clears any image on screen
	EINK_Display(gImage_github_qrcode_words, 3888); // draw the github image
}

 void SW3_configure_button(void)
 {
	 /* Port A Clock Gate Control: Clock enabled */
	 CLOCK_EnableClock(kCLOCK_PortA);

	 /* Timer configuration needed for interrupts and determining the state of the button */
	 timer_config_t timerConfig;

	 timerConfig.instance       = 0U;
	 timerConfig.srcClock_Hz    = TIMER_SOURCE_CLOCK;
	 timerConfig.clockSrcSelect = 0U;
	 TM_Init(&timerConfig);

	 /* Set up port pin for the button SW3*/
	 const port_pin_config_t porta4_pin38_config = {
			 kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			 kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			 kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
			 kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			 kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			 kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			 kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	 };

	PORT_SetPinConfig(PORTA, PIN4_IDX, &porta4_pin38_config);  /* PORTA4 (pin 38) is configured as PTA4 */

	/* Button configuration sequence */
	static BUTTON_HANDLE_DEFINE(buttonHandle);
	button_config_t buttonConfig;
	buttonConfig.gpio.direction = kHAL_GpioDirectionIn,
	buttonConfig.gpio.port = 0;
	buttonConfig.gpio.pin  = BOARD_SW3_GPIO_PIN; // PORTA6
	buttonConfig.gpio.pinStateDefault = 1;
	BUTTON_Init((button_handle_t) buttonHandle, &buttonConfig);
	BUTTON_InstallCallback((button_handle_t) buttonHandle, button_callback, NULL);
 }

 button_status_t button_callback(void *buttonHandle, button_callback_message_t *message, void *callbackParam)
 {
     button_status_t status = kStatus_BUTTON_Success;

     /* Set the display_state based on the type of button press */
     switch (message->event)
     {
         case kBUTTON_EventOneClick:
             PRINTF("kBUTTON_EventOneClick\r\n");
             display_state = kDisplay_PrintPrimaryImage;
             break;
         case kBUTTON_EventShortPress:
             PRINTF("kBUTTON_EventShortPress\r\n");
             display_state = kDisplay_PrintSecondImage;
             break;
         case kBUTTON_EventDoubleClick:
             PRINTF("kBUTTON_EventDoubleClick\r\n");
             display_state = kDisplay_PrintThirdImage;
             break;
         case kBUTTON_EventLongPress:
             PRINTF("kBUTTON_EventLongPress\r\n");
             display_state = kDisplay_Clear;
             break;
         case kBUTTON_EventError:
             PRINTF("kBUTTON_EventError\r\n");
             break;
         default:
             status = kStatus_BUTTON_Error;
             break;
     }

     return status;
 }



/*******************************************************************************
 * Main Code
 ******************************************************************************/

/*
 * @brief   Application entry point.
 */
int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Welcome to the E-INK Display\r\n");

    /* Initialize SW3 button on FRDM board*/
    SW3_configure_button();

	/*SPI and EINK display initialization*/
	EINK_InitSequenceSPI();

	display_state = kDisplay_PrintPrimaryImage; // start by printing the primary image


	/* Super-loop checking for changes resulting from button press. */
    while(1) {

    	if (display_state == kDisplay_Clear)
    	{
    		EINK_Clear();
    		display_state = kDisplay_DoNothing;
    	}
    	else if (display_state == kDisplay_PrintPrimaryImage)
		{
    		displayPrimaryImage();
			display_state = kDisplay_DoNothing;
		}
    	else if (display_state == kDisplay_PrintSecondImage)
		{
    		displaySecondaryImage();
    		display_state = kDisplay_DoNothing;
		}
    	else if (display_state == kDisplay_PrintThirdImage)
		{
			displayThirdImage();
			display_state = kDisplay_DoNothing;
		}
    }

    return 0 ;
}

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
