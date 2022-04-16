/*
 * eink.k
 *
 * Copyright 2022 Santiago Gomez
 * All rights reserved.
 *
 *   Created on: Apr 15, 2022
 *       Author: Santiago Gomez
 *
 */

#ifndef EINK_H_
#define EINK_H_

/***********************************************************************************************************************
 * EINK API
 **********************************************************************************************************************/

/*
 * @brief   Application entry point.
 */

#if defined(__cplusplus)
extern "C" {
#endif




#include "fsl_dspi.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"  // gives access to PRINTF()

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define EINK_2IN9_V2_WIDTH  128
#define EINK_2IN9_V2_HEIGHT 296

#define TEST_IMAGE_SIZE     2048


/*! @brief High/Low definition */
typedef enum _gpio_pin_hi_low
{
    kGPIO_Low  = 0U,
    kGPIO_Hi = 1U,
} gpio_pin_hi_low_t;

// the controller is the k64 FRDM board
#define DSPI_CONTOLLER_BASEADDR                 SPI0
#define DSPI_CONTOLLER_CLK_SRC                  DSPI0_CLK_SRC
#define DSPI_CONTOLLER_CLK_FREQ                 CLOCK_GetFreq(DSPI0_CLK_SRC)
#define DSPI_CONTOLLER_PCS_FOR_INIT             kDSPI_Pcs0
#define DSPI_CONTOLLER_PCS_FOR_TRANSFER         kDSPI_MasterPcs0
#define DSPI_DEALY_COUNT                        0xfffffU
#define TRANSFER_BAUDRATE 						500000U /*! Transfer baudrate - 500k */

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */


// Symbols for E-INK LED on FRDM board
/* Symbols to be used with GPIO driver */
#define EINK_LED_BLUE_GPIO GPIOB                 /*!<@brief GPIO peripheral base pointer */
#define EINK_LED_BLUE_GPIO_PIN_MASK (1U << 21U)  /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define EINK_LED_BLUE_PORT PORTB                 /*!<@brief PORT peripheral base pointer */
#define EINK_LED_BLUE_PIN  21U                   /*!<@brief PORT pin number */
#define EINK_LED_BLUE_MASK (1U << 21U)           /*!<@brief PORT pin mask */
                                                  /* @} */

// Symbols for E-INK DC pin
/* Symbols to be used with GPIO driver */
#define EINK_DC_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define EINK_DC_GPIO_PIN_MASK (1U << 4U)  /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define EINK_DC_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define EINK_DC_PIN  4U                   /*!<@brief PORT pin number */
#define EINK_DC_PIN_MASK (1U << 4U)       /*!<@brief PORT pin mask */
                                                /* @} */

// Symbols for E-INK CS pin
/* Symbols to be used with GPIO driver */
#define EINK_CS_GPIO GPIOC                /*!<@brief GPIO peripheral base pointer */
#define EINK_CS_GPIO_PIN_MASK (1U << 3U)  /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define EINK_CS_PORT PORTC                /*!<@brief PORT peripheral base pointer */
#define EINK_CS_PIN 3U                    /*!<@brief PORT pin number */
#define EINK_CS_PIN_MASK (1U << 3U)       /*!<@brief PORT pin mask */
                                                /* @} */


// Symbols for E-INK RST pin
/* Symbols to be used with GPIO driver */
#define EINK_RST_GPIO GPIOC                 /*!<@brief GPIO peripheral base pointer */
#define EINK_RST_GPIO_PIN_MASK (1U << 12U)  /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define EINK_RST_PORT PORTC                 /*!<@brief PORT peripheral base pointer */
#define EINK_RST_PIN 12U                    /*!<@brief PORT pin number */
#define EINK_RST_PIN_MASK (1U << 12U)       /*!<@brief PORT pin mask */
                                                /* @} */

// Symbols for E-INK BUSY pin
/* Symbols to be used with GPIO driver */
#define EINK_BUSY_GPIO GPIOE                 /*!<@brief GPIO peripheral base pointer */
#define EINK_BUSY_GPIO_PIN_MASK (1U << 26U)  /*!<@brief GPIO pin mask */

/* Symbols to be used with PORT driver */
#define EINK_BUSY_PORT PORTE                 /*!<@brief PORT peripheral base pointer */
#define EINK_BUSY_PIN 26U                    /*!<@brief PORT pin number */
#define EINK_BUSY_PIN_MASK (1U << 26U)       /*!<@brief PORT pin mask */
                                                /* @} */

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile extern uint32_t g_systickCounter_eink; // needed for creating system delay
volatile extern uint8_t _WF_PARTIAL_2IN9[159]; // provided by Waveshare sample code
volatile extern uint8_t WS_20_30[159]; // provided by Waveshare sample code
volatile extern UBYTE gImage_test_qrcode[TEST_IMAGE_SIZE]; // sample image to testing

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void SysTick_Handler(void);
extern void Delay_Config(void);
extern void delay_ms(uint32_t delay);
extern void EINK_test(void);
extern void EINK_GPIO_PINS(void);
extern void EINK_Init(void);
extern void EINK_Clear(void);
extern void EINK_Display(UBYTE *Image, UWORD Image_Size);
extern void EINK_ReadBusy(void);
static void EINK_TurnOnDisplay(void);
static void EINK_TurnOnDisplay_Partial(void);
static void EINK_SendCommand(UBYTE byte);
static void EINK_SendData(UBYTE byte);
static void EINK_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend);
static void EINK_SetCursor(UWORD Xstart, UWORD Ystart);
static void EINK_LUT(UBYTE *lut);
static void EINK_LUT_by_host(UBYTE *lut);
static void EINK_Reset(void);


extern void EINK_InitSequenceSPI(void);
extern void EINK_InitPins(void);
extern void EINK_InitSPI(void);

#if defined(__cplusplus)
}
#endif

#endif /* EINK_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
