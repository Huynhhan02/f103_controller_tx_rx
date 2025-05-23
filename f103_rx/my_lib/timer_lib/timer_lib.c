/*
 * timer_lib.c
 *
 *  Created on: May 6, 2025
 *      Author: deffen
 */


#include "timer_lib.h"

void timer2_init()
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
void timer3_pwm_init()
{
	APB1_clk_setup(TIM3en);
	APB2_clk_setup(GPIOAen);
	APB2_clk_setup(GPIOBen);
	uint32_t* GPIOA_CRL = (uint32_t*) 0x40010800;
	uint32_t* GPIOB_CRL = (uint32_t*) 0x40010c00;
	*GPIOA_CRL &= ~(0xff<<24);
	*GPIOB_CRL &= ~(0xff<<0);
	*GPIOA_CRL |= (0b10111011<<24);
	*GPIOB_CRL |= (0b10111011<<0);


//		uint32_t* TIM1_DIER = (uint32_t*)(TIM1_BASE + 0x0c);
//		*TIM1_DIER |= 1;
		uint32_t* PSC = (uint32_t*)0x40000428;
		*PSC = 71;
		uint32_t* ARR = (uint32_t*)0x4000042c;
		*ARR = 99;
		uint32_t* CNT = (uint32_t*)0x40000424;
		*CNT = 0;

		uint32_t* CCMR1 = (uint32_t*)0x40000418;
		*CCMR1 |= (0b110 << 12) | (0b110<<4);
		uint32_t* CCMR2 = (uint32_t*)0x4000041c;
		*CCMR2 |= (0b110 << 12) | (0b110<<4);
		uint32_t* CCER = (uint32_t*)0x40000420;
		*CCER |= (1<<0) | (1<<4) | (1<<8) | (1<<12);

		uint32_t* CCR1 = (uint32_t*)0x40000434;
		*CCR1 = 50;
		uint32_t* CCR2 = (uint32_t*)0x40000438;
		*CCR2 = 50;
		uint32_t* CCR3 = (uint32_t*)0x4000043c;
		*CCR3 = 50;
		uint32_t* CCR4 = (uint32_t*)0x40000440;
		*CCR4 = 50;


		uint32_t* CR1 = (uint32_t*)0x40000400;
		*CR1 |= (1<<7);
		*CR1 |= 1;
}

void timer4_pwm_init()
{
	APB1_clk_setup(TIM4en);
//	APB2_clk_setup(GPIOAen);
	APB2_clk_setup(GPIOBen);
	uint32_t* GPIOB_CRL = (uint32_t*) 0x40010c00;
	uint32_t* GPIOB_CRH = (uint32_t*) 0x40010c04;
	*GPIOB_CRL &= ~(0xff<<24);
	*GPIOB_CRH &= ~(0xff<<0);
	*GPIOB_CRL |= (0b10111011<<24);
	*GPIOB_CRH |= (0b10111011<<0);


//		uint32_t* TIM1_DIER = (uint32_t*)(TIM1_BASE + 0x0c);
//		*TIM1_DIER |= 1;
		uint32_t* PSC = (uint32_t*)0x40000828;
		*PSC = 71;
		uint32_t* ARR = (uint32_t*)0x4000082c;
		*ARR = 99;
		uint32_t* CNT = (uint32_t*)0x40000824;
		*CNT = 0;

		uint32_t* CCMR1 = (uint32_t*)0x40000818;
		*CCMR1 |= (0b110 << 12) | (0b110<<4);
		uint32_t* CCMR2 = (uint32_t*)0x4000081c;
		*CCMR2 |= (0b110 << 12) | (0b110<<4);
		uint32_t* CCER = (uint32_t*)0x40000820;
		*CCER |= (1<<0) | (1<<4) | (1<<8) | (1<<12);

		uint32_t* CCR1 = (uint32_t*)0x40000834;
		*CCR1 = 50;
		uint32_t* CCR2 = (uint32_t*)0x40000838;
		*CCR2 = 50;
		uint32_t* CCR3 = (uint32_t*)0x4000083c;
		*CCR3 = 50;
		uint32_t* CCR4 = (uint32_t*)0x40000840;
		*CCR4 = 50;


		uint32_t* CR1 = (uint32_t*)0x40000800;
		*CR1 |= (1<<7);
		*CR1 |= 1;
}

void delay(int ms)
{
	uint32_t* CNT = (uint32_t*)0x40000024;
	*CNT = 0;
	uint32_t dl = ms*10;
	while(*CNT<dl);
}
