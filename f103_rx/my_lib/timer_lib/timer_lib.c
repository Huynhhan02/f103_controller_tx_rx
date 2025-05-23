/*
 * timer_lib.c
 *
 *  Created on: May 6, 2025
 *      Author: deffen
 */


#include "timer_lib.h"

void timer_init()
{
	  APB1_clk_setup(TIM2en);

//		uint32_t* TIM1_DIER = (uint32_t*)(TIM1_BASE + 0x0c);
//		*TIM1_DIER |= 1;
		uint32_t* PSC = (uint32_t*)0x40000028;
		*PSC = 7200;
//		uint32_t* ARR = (uint32_t*)0x4000002c;
//		*ARR =
		uint32_t* CR1 = (uint32_t*)0x40000000;
		*CR1 |= 1;
//		uint32_t* ARR = (uint32_t*)0x4000142c;
//		*ARR = 2000;

//		uint32_t* NVIC_ISER0 = (uint32_t*) 0xE000E100;
//		*NVIC_ISER0 |= 1<<25;
}

void delay(int ms)
{
	uint32_t* CNT = (uint32_t*)0x40000024;
	*CNT = 0;
	uint32_t dl = ms*10;
	while(*CNT<dl);
}
