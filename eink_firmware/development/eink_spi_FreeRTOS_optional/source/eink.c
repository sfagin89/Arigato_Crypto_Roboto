/*
 * eink.c
 *
 * Copyright 2022 Santiago Gomez
 * All rights reserved.
 *
 *  Created on: Apr 15, 2022
 *      Author: Santiago Gomez
 */

#include "eink.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter_eink  = 20U;

volatile uint8_t _WF_PARTIAL_2IN9[159] =
{
	0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0A,0x0,0x0,0x0,0x0,0x0,0x2,
	0x1,0x0,0x0,0x0,0x0,0x0,0x0,
	0x1,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
	0x22,0x17,0x41,0xB0,0x32,0x36,
};

volatile uint8_t WS_20_30[159] =
{
	0x80,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x40,	0x0,	0x0,	0x0,
	0x10,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x20,	0x0,	0x0,	0x0,
	0x80,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x40,	0x0,	0x0,	0x0,
	0x10,	0x66,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x20,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x14,	0x8,	0x0,	0x0,	0x0,	0x0,	0x1,
	0xA,	0xA,	0x0,	0xA,	0xA,	0x0,	0x1,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x14,	0x8,	0x0,	0x1,	0x0,	0x0,	0x1,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x1,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
	0x44,	0x44,	0x44,	0x44,	0x44,	0x44,	0x0,	0x0,	0x0,
	0x22,	0x17,	0x41,	0x0,	0x32,	0x36
};

volatile UBYTE gImage_test_qrcode[TEST_IMAGE_SIZE] = { /* 0X00,0X01,0X80,0X00,0X80,0X00, */
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X00,0X3E,0X00,0X00,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X00,0X3E,0X00,0X00,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X00,0X3E,0X00,0X00,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X00,0X3E,0X00,0X00,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7C,0X00,0X00,0X1F,0X0F,0XFF,0X80,0X3E,0X01,0XF0,0XF8,0X00,0X00,0X3E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XFF,0X80,0X3E,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XFF,0X80,0X3E,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XFF,0X80,0X3E,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XFF,0X80,0X3E,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0X83,0XFE,0X00,0X00,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0X83,0XFE,0X00,0X00,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0X83,0XFE,0X00,0X00,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0X83,0XFE,0X00,0X00,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0X83,0XFE,0X1F,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0X83,0XFE,0X1F,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0X83,0XFE,0X1F,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0X83,0XFE,0X1F,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X07,0X80,0X01,0XE1,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0X80,0X01,0XE1,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0X80,0X01,0XE1,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0X80,0X01,0XE1,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0X80,0X01,0XE1,0XF0,0XF8,0X7F,0XFC,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X78,0X03,0XC1,0XE1,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X78,0X03,0XC1,0XE1,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X78,0X03,0XC1,0XE1,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X78,0X03,0XC1,0XE1,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X87,0X83,0XC1,0XE1,0XF0,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X87,0X83,0XC1,0XE1,0XF0,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X87,0X83,0XC1,0XE1,0XF0,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X87,0X83,0XC1,0XE1,0XF0,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X87,0X83,0XC1,0XE1,0XF0,0XFF,0XFF,0XFF,0XFE,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X7C,0X3E,0X01,0XF0,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X7C,0X3E,0X01,0XF0,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X7C,0X3E,0X01,0XF0,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X7C,0X3E,0X01,0XF0,0X00,0X00,0X00,0X00,0X00,
		0X00,0X78,0X03,0XFF,0XFF,0XFF,0X80,0X03,0XC1,0XE1,0XFF,0X00,0X7C,0X3F,0XFE,0X00,
		0X00,0X78,0X03,0XFF,0XFF,0XFF,0X80,0X03,0XC1,0XE1,0XFF,0X00,0X7C,0X3F,0XFE,0X00,
		0X00,0X78,0X03,0XFF,0XFF,0XFF,0X80,0X03,0XC1,0XE1,0XFF,0X00,0X7C,0X3F,0XFE,0X00,
		0X00,0X78,0X03,0XFF,0XFF,0XFF,0X80,0X03,0XC1,0XE1,0XFF,0X00,0X7C,0X3F,0XFE,0X00,
		0X00,0X78,0X03,0XFF,0XFF,0XFF,0X80,0X03,0XC1,0XE1,0XFF,0X00,0X7C,0X3F,0XFE,0X00,
		0X00,0X78,0X03,0XC1,0XE0,0XFF,0X80,0X7F,0XC1,0XFE,0X0F,0X07,0XFF,0XFF,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XE0,0XFF,0X80,0X7F,0XC1,0XFE,0X0F,0X07,0XFF,0XFF,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XE0,0XFF,0X80,0X7F,0XC1,0XFE,0X0F,0X07,0XFF,0XFF,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XE0,0XFF,0X80,0X7F,0XC1,0XFE,0X0F,0X07,0XFF,0XFF,0XE0,0X00,
		0X00,0X78,0X00,0X3E,0X1F,0X0F,0XF8,0X03,0XFF,0XFE,0X00,0XFF,0X83,0XC0,0X1E,0X00,
		0X00,0X78,0X00,0X3E,0X1F,0X0F,0XF8,0X03,0XFF,0XFE,0X00,0XFF,0X83,0XC0,0X1E,0X00,
		0X00,0X78,0X00,0X3E,0X1F,0X0F,0XF8,0X03,0XFF,0XFE,0X00,0XFF,0X83,0XC0,0X1E,0X00,
		0X00,0X78,0X00,0X3E,0X1F,0X0F,0XF8,0X03,0XFF,0XFE,0X00,0XFF,0X83,0XC0,0X1E,0X00,
		0X00,0X78,0X03,0XC0,0X00,0XF0,0X78,0X7C,0X01,0XE0,0X00,0X07,0X83,0XFF,0XFE,0X00,
		0X00,0X78,0X03,0XC0,0X00,0XF0,0X78,0X7C,0X01,0XE0,0X00,0X07,0X83,0XFF,0XFE,0X00,
		0X00,0X78,0X03,0XC0,0X00,0XF0,0X78,0X7C,0X01,0XE0,0X00,0X07,0X83,0XFF,0XFE,0X00,
		0X00,0X78,0X03,0XC0,0X00,0XF0,0X78,0X7C,0X01,0XE0,0X00,0X07,0X83,0XFF,0XFE,0X00,
		0X00,0X78,0X03,0XC0,0X00,0XF0,0X78,0X7C,0X01,0XE0,0X00,0X07,0X83,0XFF,0XFE,0X00,
		0X00,0X07,0XC0,0X01,0XFF,0X00,0X07,0XFF,0XC0,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X07,0XC0,0X01,0XFF,0X00,0X07,0XFF,0XC0,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X07,0XC0,0X01,0XFF,0X00,0X07,0XFF,0XC0,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X07,0XC0,0X01,0XFF,0X00,0X07,0XFF,0XC0,0X01,0XF0,0XF8,0X00,0X00,0X1E,0X00,
		0X00,0X78,0X3C,0X3E,0X00,0XFF,0XF8,0X03,0XC1,0XFF,0XFF,0X00,0X7C,0X03,0XE0,0X00,
		0X00,0X78,0X3C,0X3E,0X00,0XFF,0XF8,0X03,0XC1,0XFF,0XFF,0X00,0X7C,0X03,0XE0,0X00,
		0X00,0X78,0X3C,0X3E,0X00,0XFF,0XF8,0X03,0XC1,0XFF,0XFF,0X00,0X7C,0X03,0XE0,0X00,
		0X00,0X78,0X3C,0X3E,0X00,0XFF,0XF8,0X03,0XC1,0XFF,0XFF,0X00,0X7C,0X03,0XE0,0X00,
		0X00,0X78,0X3C,0X3E,0X00,0XFF,0XF8,0X03,0XC1,0XFF,0XFF,0X00,0X7C,0X03,0XE0,0X00,
		0X00,0X7F,0XC0,0X3F,0XFF,0X0F,0XF8,0X00,0X3E,0X1E,0X0F,0XF8,0X7F,0XFF,0XFE,0X00,
		0X00,0X7F,0XC0,0X3F,0XFF,0X0F,0XF8,0X00,0X3E,0X1E,0X0F,0XF8,0X7F,0XFF,0XFE,0X00,
		0X00,0X7F,0XC0,0X3F,0XFF,0X0F,0XF8,0X00,0X3E,0X1E,0X0F,0XF8,0X7F,0XFF,0XFE,0X00,
		0X00,0X7F,0XC0,0X3F,0XFF,0X0F,0XF8,0X00,0X3E,0X1E,0X0F,0XF8,0X7F,0XFF,0XFE,0X00,
		0X00,0X78,0X3C,0X01,0XE0,0X00,0X7F,0XFC,0X01,0XE0,0X0F,0X07,0X83,0XFC,0X1E,0X00,
		0X00,0X78,0X3C,0X01,0XE0,0X00,0X7F,0XFC,0X01,0XE0,0X0F,0X07,0X83,0XFC,0X1E,0X00,
		0X00,0X78,0X3C,0X01,0XE0,0X00,0X7F,0XFC,0X01,0XE0,0X0F,0X07,0X83,0XFC,0X1E,0X00,
		0X00,0X78,0X3C,0X01,0XE0,0X00,0X7F,0XFC,0X01,0XE0,0X0F,0X07,0X83,0XFC,0X1E,0X00,
		0X00,0X78,0X03,0XC1,0XFF,0XF0,0X7F,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XFF,0XF0,0X7F,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XFF,0XF0,0X7F,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XFF,0XF0,0X7F,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XE0,0X00,
		0X00,0X78,0X03,0XC1,0XFF,0XF0,0X7F,0X83,0XFF,0XFF,0XFF,0XFF,0XFC,0X3F,0XE0,0X00,
		0X00,0X00,0X00,0X00,0X00,0X0F,0X87,0X83,0XFE,0X01,0XF0,0X00,0X7C,0X3F,0XE0,0X00,
		0X00,0X00,0X00,0X00,0X00,0X0F,0X87,0X83,0XFE,0X01,0XF0,0X00,0X7C,0X3F,0XE0,0X00,
		0X00,0X00,0X00,0X00,0X00,0X0F,0X87,0X83,0XFE,0X01,0XF0,0X00,0X7C,0X3F,0XE0,0X00,
		0X00,0X00,0X00,0X00,0X00,0X0F,0X87,0X83,0XFE,0X01,0XF0,0X00,0X7C,0X3F,0XE0,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X7C,0X00,0X01,0XF0,0XF8,0X7C,0X00,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X7C,0X00,0X01,0XF0,0XF8,0X7C,0X00,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X7C,0X00,0X01,0XF0,0XF8,0X7C,0X00,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X7C,0X00,0X01,0XF0,0XF8,0X7C,0X00,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X7C,0X00,0X01,0XF0,0XF8,0X7C,0X00,0X1E,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XF8,0X00,0X3F,0XFF,0XF0,0X00,0X7C,0X00,0X00,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XF8,0X00,0X3F,0XFF,0XF0,0X00,0X7C,0X00,0X00,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XF8,0X00,0X3F,0XFF,0XF0,0X00,0X7C,0X00,0X00,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X0F,0XF8,0X00,0X3F,0XFF,0XF0,0X00,0X7C,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XFC,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0XFF,0XFF,0XC1,0XFF,0XFF,0XFF,0XF8,0X00,0X00,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0XFC,0X01,0XE1,0XF0,0XF8,0X00,0X03,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0XFC,0X01,0XE1,0XF0,0XF8,0X00,0X03,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0XFC,0X01,0XE1,0XF0,0XF8,0X00,0X03,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X0F,0X87,0XFC,0X01,0XE1,0XF0,0XF8,0X00,0X03,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0XFC,0X3F,0XFF,0XFF,0X00,0X7F,0XFF,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0XFC,0X3F,0XFF,0XFF,0X00,0X7F,0XFF,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0XFC,0X3F,0XFF,0XFF,0X00,0X7F,0XFF,0XFE,0X00,
		0X00,0X78,0X3F,0XFE,0X1F,0X00,0X07,0XFC,0X3F,0XFF,0XFF,0X00,0X7F,0XFF,0XFE,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X00,0X00,0X01,0XE0,0X00,0X07,0XFC,0X3F,0XFE,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X00,0X00,0X01,0XE0,0X00,0X07,0XFC,0X3F,0XFE,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X00,0X00,0X01,0XE0,0X00,0X07,0XFC,0X3F,0XFE,0X00,
		0X00,0X78,0X00,0X00,0X1F,0X00,0X00,0X00,0X01,0XE0,0X00,0X07,0XFC,0X3F,0XFE,0X00,
		0X00,0X7C,0X00,0X00,0X1F,0X00,0X00,0X00,0X01,0XE0,0X00,0X07,0XFC,0X3F,0XFE,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X03,0XC0,0X01,0XFF,0X00,0X03,0XC0,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X03,0XC0,0X01,0XFF,0X00,0X03,0XC0,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X03,0XC0,0X01,0XFF,0X00,0X03,0XC0,0X1E,0X00,
		0X00,0X7F,0XFF,0XFF,0XFF,0X0F,0X80,0X03,0XC0,0X01,0XFF,0X00,0X03,0XC0,0X1E,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
		};

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter_eink != 0U)
    {
        g_systickCounter_eink--;
    }
}

void Delay_Config(void)
{
	if (SysTick_Config(SystemCoreClock / 1000U))
	{
		while (1)
		{
		}
	}
}

void delay_ms(uint32_t delay)
{
	g_systickCounter_eink = delay;
	while (g_systickCounter_eink != 0U)
	{
	}
}

// test drawing sample image
void EINK_test(void)
{
	PRINTF("e-Paper Init and Clear...\r\n");
	Delay_Config();
	EINK_Init();
	EINK_Clear();

	EINK_Display(gImage_test_qrcode, TEST_IMAGE_SIZE);

//	PRINTF("Clear...\r\n");
//	EINK_Init();
//	EINK_Clear();

	PRINTF("Clear...\r\n");
	EINK_Clear();
}

// test the gpio pins
void EINK_GPIO_PINS(void)
{
	PRINTF("\r\nTesting EINK_GPIO_PINS\r\n");

	// write Low
	GPIO_PinWrite(EINK_LED_BLUE_GPIO, EINK_LED_BLUE_PIN, kGPIO_Hi);
	GPIO_PinWrite(EINK_LED_BLUE_GPIO, EINK_LED_BLUE_PIN, kGPIO_Low);
	GPIO_PinWrite(EINK_DC_GPIO, EINK_DC_PIN, kGPIO_Low);
	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Low);
	GPIO_PinWrite(EINK_RST_GPIO, EINK_RST_PIN, kGPIO_Low);
//	GPIO_PinWrite(EINK_BUSY_GPIO, EINK_BUSY_PIN, kGPIO_Low);

	// write Hi
	GPIO_PinWrite(EINK_LED_BLUE_GPIO, EINK_LED_BLUE_PIN, kGPIO_Hi);
	GPIO_PinWrite(EINK_DC_GPIO, EINK_DC_PIN, kGPIO_Hi);
	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Hi);
	GPIO_PinWrite(EINK_RST_GPIO, EINK_RST_PIN, kGPIO_Hi);
//	GPIO_PinWrite(EINK_BUSY_GPIO, EINK_BUSY_PIN, kGPIO_Hi);


}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
void EINK_Init(void)
{
	EINK_Reset();

	delay_ms(100U);

	EINK_ReadBusy();
	EINK_SendCommand(0x12);  //SWRESET
	EINK_ReadBusy();

	EINK_SendCommand(0x01); //Driver output control
	EINK_SendData(0x27);
	EINK_SendData(0x01);
	EINK_SendData(0x00);

	EINK_SendCommand(0x11); //data entry mode
	EINK_SendData(0x03);

	EINK_SetWindows(0, 0, EINK_2IN9_V2_WIDTH-1, EINK_2IN9_V2_HEIGHT-1);

	// EPD_2IN9_V2_SendCommand(0x3C); //BorderWavefrom
	// EPD_2IN9_V2_SendData(0x05);

	EINK_SendCommand(0x21); //  Display update control
	EINK_SendData(0x00);
	EINK_SendData(0x80);

	// EPD_2IN9_V2_SendCommand(0x18); //Read built-in temperature sensor, commented out by Waveshare sample code
	// EPD_2IN9_V2_SendData(0x80); // commented out by Waveshare sample code

	EINK_SetCursor(0, 0);
	EINK_ReadBusy();

	EINK_LUT_by_host(WS_20_30);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EINK_Clear(void)
{
	UWORD i;
	EINK_SendCommand(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<4736;i++)
	{
		EINK_SendData(0xff);
	}
	EINK_TurnOnDisplay();
}

/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EINK_Display(UBYTE *Image, UWORD Image_Size)
{
	UWORD i;
	EINK_SendCommand(0x24);   //write RAM for black(0)/white (1)
	for(i=0;i<Image_Size/*4736*/;i++)
	{
		EINK_SendData(Image[i]);
	}
	EINK_TurnOnDisplay();
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EINK_ReadBusy(void)
{
//    Debug("e-Paper busy\r\n");
	while(1)
	{	 //=1 BUSY
		if(GPIO_PinRead(EINK_BUSY_GPIO, EINK_BUSY_PIN)==0)
			break;
		delay_ms(50U);
	}
	delay_ms(50U);
	PRINTF("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void EINK_TurnOnDisplay(void)
{
	EINK_SendCommand(0x22); //Display Update Control
	EINK_SendData(0xc7);
	EINK_SendCommand(0x20); //Activate Display Update Sequence
	EINK_ReadBusy();
}

static void EINK_TurnOnDisplay_Partial(void)
{
	EINK_SendCommand(0x22); //Display Update Control
	EINK_SendData(0x0F);
	EINK_SendCommand(0x20); //Activate Display Update Sequence
	EINK_ReadBusy();
}

/******************************************************************************
function :	Send 1 byte command to eink display
parameter:
******************************************************************************/
static void EINK_SendCommand(UBYTE byte)
{
	GPIO_PinWrite(EINK_DC_GPIO, EINK_DC_PIN, kGPIO_Low);
	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Low);

	// spi transfer goes, the controller is the K64 FRDM board
	/* Start controller transfer, send data to screen */
	dspi_transfer_t controllerXfer;
	controllerXfer.txData      = &byte; // transferring the byte passed in
	controllerXfer.rxData      = NULL;
	controllerXfer.dataSize    = 1U; // only transferring one byte
	controllerXfer.configFlags = kDSPI_MasterCtar0 | DSPI_CONTOLLER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
	DSPI_MasterTransferBlocking(DSPI_CONTOLLER_BASEADDR, &controllerXfer);

	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Hi);
}


/******************************************************************************
function :	Send data to eink display
parameter:
******************************************************************************/
static void EINK_SendData(UBYTE byte)
{
	GPIO_PinWrite(EINK_DC_GPIO, EINK_DC_PIN, kGPIO_Hi);
	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Low);

	// spi transfer goes, the controller is the K64 FRDM board
	/* Start controller transfer, send data to screen */
	dspi_transfer_t controllerXfer;
	controllerXfer.txData      = &byte; // transferring the byte passed in
	controllerXfer.rxData      = NULL;
	controllerXfer.dataSize    = 1U; // only transferring one byte
	controllerXfer.configFlags = kDSPI_MasterCtar0 | DSPI_CONTOLLER_PCS_FOR_TRANSFER | kDSPI_MasterPcsContinuous;
	DSPI_MasterTransferBlocking(DSPI_CONTOLLER_BASEADDR, &controllerXfer);

	GPIO_PinWrite(EINK_CS_GPIO, EINK_CS_PIN, kGPIO_Hi);
}


/******************************************************************************
function :	Setting the display window
parameter:
******************************************************************************/
static void EINK_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    EINK_SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    EINK_SendData((Xstart>>3) & 0xFF);
    EINK_SendData((Xend>>3) & 0xFF);
    EINK_SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    EINK_SendData(Ystart & 0xFF);
    EINK_SendData((Ystart >> 8) & 0xFF);
    EINK_SendData(Yend & 0xFF);
    EINK_SendData((Yend >> 8) & 0xFF);
}

/******************************************************************************
function :	Set Cursor
parameter:
******************************************************************************/
static void EINK_SetCursor(UWORD Xstart, UWORD Ystart)
{
    EINK_SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
    EINK_SendData(Xstart & 0xFF);

    EINK_SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    EINK_SendData(Ystart & 0xFF);
    EINK_SendData((Ystart >> 8) & 0xFF);
}


/******************************************************************************
function :	LUTs provided Waveshare sample code
parameter:
******************************************************************************/
static void EINK_LUT(UBYTE *lut)
{
	UBYTE count;
	EINK_SendCommand(0x32);
	for(count=0; count<153; count++)
		EINK_SendData(lut[count]);
	EINK_ReadBusy();
}

static void EINK_LUT_by_host(UBYTE *lut)
{
	EINK_LUT((UBYTE *)lut);			//lut
	EINK_SendCommand(0x3f);
	EINK_SendData(*(lut+153));
	EINK_SendCommand(0x03);	// gate voltage
	EINK_SendData(*(lut+154));
	EINK_SendCommand(0x04);	// source voltage
	EINK_SendData(*(lut+155));	// VSH
	EINK_SendData(*(lut+156));	// VSH2
	EINK_SendData(*(lut+157));	// VSL
	EINK_SendCommand(0x2c);		// VCOM
	EINK_SendData(*(lut+158));

}

/******************************************************************************
function :	Software reset in the eink micro-controller
parameter:
******************************************************************************/
static void EINK_Reset(void)
{
	GPIO_PinWrite(EINK_RST_GPIO, EINK_RST_PIN, kGPIO_Hi);

	delay_ms(100U);

    GPIO_PinWrite(EINK_RST_GPIO, EINK_RST_PIN, kGPIO_Low);

    delay_ms(2U);

    GPIO_PinWrite(EINK_RST_GPIO, EINK_RST_PIN, kGPIO_Hi);

    delay_ms(100U);
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void EINK_InitSequenceSPI(void)
{
	Delay_Config();  // 1)   configure delay
	EINK_InitPins(); // 2) initialize the GPIO and SPI pins
	EINK_InitSPI();  // 3) initialize SPI module
	EINK_Init();     // 4) initialize eink display

}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : EINK_InitPins
 * Description   : Configures pin routing and optionally pin electrical features for SPI interface with EINK display.
 *
 * END ****************************************************************************************************************/
void EINK_InitPins(void)
{
	/****** Start for GPIO pins ******/

	/* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

	/* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

	/* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t EINK_LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB22 (pin 68)  */
    GPIO_PinInit(EINK_LED_BLUE_GPIO, EINK_LED_BLUE_PIN, &EINK_LED_BLUE_config);


	gpio_pin_config_t EINK_DC_config = {
	        .pinDirection = kGPIO_DigitalOutput,
	        .outputLogic = 0U // default is 0 because DC low means data interpreted as command
	};
	/* Initialize GPIO functionality on pin PTC4 (pin 76)  */
	GPIO_PinInit(EINK_DC_GPIO, EINK_DC_PIN, &EINK_DC_config);


	gpio_pin_config_t EINK_CS_config = {
		        .pinDirection = kGPIO_DigitalOutput,
		        .outputLogic = 1U
	};
	/* Initialize GPIO functionality on pin PTC3 (pin 73)  */
	GPIO_PinInit(EINK_CS_GPIO, EINK_CS_PIN, &EINK_CS_config);


	gpio_pin_config_t EINK_RST_config = {
	        .pinDirection = kGPIO_DigitalOutput,
	        .outputLogic = 1U
	};
	/* Initialize GPIO functionality on pin PTC12 (pin 84)  */
	GPIO_PinInit(EINK_RST_GPIO, EINK_RST_PIN, &EINK_RST_config);


	gpio_pin_config_t EINK_BUSY_config = {
	        .pinDirection = kGPIO_DigitalInput,
	        .outputLogic = 0U
	};
	/* Initialize GPIO functionality on pin PTE26 (pin 33)  */
	GPIO_PinInit(EINK_BUSY_GPIO, EINK_BUSY_PIN, &EINK_BUSY_config);

	/* PORTB (pin 67) is configured as PTC4 */
	PORT_SetPinMux(EINK_LED_BLUE_PORT, EINK_LED_BLUE_PIN, kPORT_MuxAsGpio);

	/* PORTC4 (pin 76) is configured as PTC4 */
	PORT_SetPinMux(EINK_DC_PORT, EINK_DC_PIN, kPORT_MuxAsGpio);

	/* PORTC3 (pin 73) is configured as PTC3 */
	PORT_SetPinMux(EINK_CS_PORT, EINK_CS_PIN, kPORT_MuxAsGpio);

	/* PORTC12 (pin 84) is configured as PTC12 */
	PORT_SetPinMux(EINK_RST_PORT, EINK_RST_PIN, kPORT_MuxAsGpio);

	/* PORTE26 (pin 33) is configured as PTE26 */
	PORT_SetPinMux(EINK_BUSY_PORT, EINK_BUSY_PIN, kPORT_MuxAsGpio);


	/****** Start for SPI pins ******/

    /* PORTB16 (pin 62) is configured as UART0_RX */
    PORT_SetPinMux(PORTB, 16U, kPORT_MuxAlt3);

    /* PORTB17 (pin 63) is configured as UART0_TX */
    PORT_SetPinMux(PORTB, 17U, kPORT_MuxAlt3);

    /* PORTD0 (pin 93) is configured as SPI0_PCS0 */
    PORT_SetPinMux(PORTD, 0U, kPORT_MuxAlt2);

    /* PORTD1 (pin 94) is configured as SPI0_SCK */
    PORT_SetPinMux(PORTD, 1U, kPORT_MuxAlt2);

    /* PORTD2 (pin 95) is configured as SPI0_SOUT */
    PORT_SetPinMux(PORTD, 2U, kPORT_MuxAlt2);

    /* PORTD3 (pin 96) is configured as SPI0_SIN */
    PORT_SetPinMux(PORTD, 3U, kPORT_MuxAlt2);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : EINK_InitSPI
 * Description   : Configures and initializes SPI module.
 *
 * END ****************************************************************************************************************/

void EINK_InitSPI(void){

	uint32_t srcClock_Hz;
	dspi_master_config_t controllerConfig;

	/* Controller config */
	controllerConfig.whichCtar                                = kDSPI_Ctar0;
	controllerConfig.ctarConfig.baudRate                      = TRANSFER_BAUDRATE;
	controllerConfig.ctarConfig.bitsPerFrame                  = 8U;
	controllerConfig.ctarConfig.cpol                          = kDSPI_ClockPolarityActiveHigh;
	controllerConfig.ctarConfig.cpha                          = kDSPI_ClockPhaseFirstEdge;
	controllerConfig.ctarConfig.direction                     = kDSPI_MsbFirst;
	controllerConfig.ctarConfig.pcsToSckDelayInNanoSec        = 1000000000U / TRANSFER_BAUDRATE;
	controllerConfig.ctarConfig.lastSckToPcsDelayInNanoSec    = 1000000000U / TRANSFER_BAUDRATE;
	controllerConfig.ctarConfig.betweenTransferDelayInNanoSec = 1000000000U / TRANSFER_BAUDRATE;

	controllerConfig.whichPcs           = DSPI_CONTOLLER_PCS_FOR_INIT;
	controllerConfig.pcsActiveHighOrLow = kDSPI_PcsActiveLow;

	controllerConfig.enableContinuousSCK        = false;
	controllerConfig.enableRxFifoOverWrite      = false;
	controllerConfig.enableModifiedTimingFormat = false;
	controllerConfig.samplePoint                = kDSPI_SckToSin0Clock;

	srcClock_Hz = DSPI_CONTOLLER_CLK_FREQ;
	DSPI_MasterInit(DSPI_CONTOLLER_BASEADDR, &controllerConfig, srcClock_Hz);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

