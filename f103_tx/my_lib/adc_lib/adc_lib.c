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
	*CR1 |=  (1<<8);
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* JSQR = (uint32_t*)0x40012438;
	*JSQR |=  (0b11<<20) | (0b1<<15) | (2<<10) | (3<<5) | (16<<0);
	*CR2 |= (1<<15)| (0b111<<12) |(1<<0) | (1<<23) | (1<<8);
	//regular
	*CR2 |= (0b1111<<17);
	uint32_t* SQR3 = (uint32_t*)0x40012434;
	uint32_t* SQR1 = (uint32_t*)0x4001242c;
	*SQR1 |= (0b1<<20);
	*SQR3 |= (0b10<<0);



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
uint16_t read_adc_channel2()
{
	uint32_t* JDR2 = 0x40012440;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<21;
	while(((*SR>>2)&1) != 1);
	val = *JDR2;
	*SR&= ~(1<<2);
	return val;
}
uint16_t read_adc_channel3()
{
	uint32_t* JDR3 = 0x40012444;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<21;
	while(((*SR>>2)&1) != 1);
	val = *JDR3;
	*SR&= ~(1<<2);
	return val;
}
uint16_t read_adc_channel4()
{
	uint32_t* JDR4 = 0x40012448;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<21;
	while(((*SR>>2)&1) != 1);
	val = *JDR4;
	*SR&= ~(1<<2);
	return val;
}
uint16_t read_regular_CH0()
{
	uint32_t* CR1 = (uint32_t*)0x40012404;
	*CR1 |= (2<<0);
	uint32_t* DR = 0x4001244c;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<22;
//	*SR&= ~(1<<2);
	return *DR;
}
uint16_t read_regular_CH1()
{
	uint32_t* CR1 = (uint32_t*)0x40012404;
	*CR1 |= (0b100<<0);
	uint32_t* DR = 0x4001244c;
	uint32_t* CR2 = (uint32_t*)0x40012408;
	uint32_t* SR = (uint32_t*)0x40012400;
	uint16_t val;
	*CR2 |= 1<<22;
//	*SR&= ~(1<<2);
	return *DR;
}
