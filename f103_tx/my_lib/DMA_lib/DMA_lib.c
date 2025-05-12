/*
 * DMA_lib.c
 *
 *  Created on: May 3, 2025
 *      Author: deffen
 */


#include "DMA_lib.h"


void DMA_UART_init(char* data)
{
	AHB1_clk_setup(DMA1en);
//
//	uint32_t* a = (uint32_t*)0x40020004;
//	*a |= (1<<20);

	uint32_t* CNDTR5 = (uint32_t*)0x4002005c;
	*CNDTR5 = 20;

	uint32_t* CPAR5 = (uint32_t*)0x40020060;
	*CPAR5 = 0x40013804;
	uint32_t* CMAR5 = (uint32_t*)0x40020064;
	*CMAR5 = (uint32_t)data;
	uint32_t* CCR5 = (uint32_t*)0x40020058;
	*CCR5 |= ( (1<<7)| (1<<1) | (1<<2) | (1<<3) | (1<<5) );
	*CCR5 |= 1<<0;
	uint32_t* nv = (uint32_t*)0xe000e100;
	*nv |= 1<<16;

}
void DMA_ADC_init(uint16_t* data)
{
	AHB1_clk_setup(DMA1en);

	uint32_t* CNDTR1 = (uint32_t*)0x4002000c;
	*CNDTR1 = 10;
	uint32_t* CPAR1 = (uint32_t*)0x40020010;
	*CPAR1 = 0x4001244c;
	uint32_t* CMAR1 = (uint32_t*)0x40020014;
	*CMAR1 = (uint32_t)data;
	uint32_t* CCR1 = (uint32_t*)0x40020008;
	*CCR1 |= ((0b0101<<8) );
	*CCR1 |= 1<<0;
//	uint32_t* nv = (uint32_t*)0xe000e100;
//	*nv |= 1<<16;

}
