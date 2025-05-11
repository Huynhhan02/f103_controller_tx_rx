/*
 * adc_lib.c
 *
 *  Created on: May 11, 2025
 *      Author: deffen
 */


#include "adc_lib.h"

void adc_init()
{
	APB2_clk_setup(ADC1en);
	uint32_t* GPIOA_CRL = 0x40010800;
	*GPIOA_CRL &= ~(0b1111<<4);


	uint32_t* CR1 = (uint32_t*)0x40012404;
//	*CR1 |=  (1<<8);
	uint32_t* CR2 = (uint32_t*)0x40012408;
	*CR2 |= (1<<15)| (0b111<<12) |(1<<0) | (1<<23);
	uint32_t* JSQR = (uint32_t*)0x40012438;
	*JSQR |=  (0b1<<15);
}

uint16_t read_adc_channel1()
{
	uint32_t* JDR1 = 0x4001243c;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<21;
	while(((*SR>>2)&1) != 1);
	val = *JDR1;
	*SR&= ~(1<<2);
	return val;
}
uint16_t read_adc_channel4()
{
	uint32_t* JDR4 = 0x40012448;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;

	*CR2 |= 1<<21;
	while((*SR>>2 &1) == 0);
	*SR&= ~(1<<2);
	return *JDR4;
}
