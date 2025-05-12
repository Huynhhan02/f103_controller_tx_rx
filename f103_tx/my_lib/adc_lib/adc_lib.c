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
	//config PA1-PA8 = analog mode
	uint32_t* GPIOA_CRL = 0x40010800;
	uint32_t* GPIOA_CRH = 0x40010804;

	*GPIOA_CRL &= ~(0xffffffff<<0);
//	*GPIOA_CRH &= ~(0xf<<16);


	uint32_t* CR1 = (uint32_t*)0x40012404;
	*CR1 |=  (1<<8);
	uint32_t* CR2 = (uint32_t*)0x40012408;
//	uint32_t* JSQR = (uint32_t*)0x40012438;
//	*JSQR |=  (0b11<<20) | (0b1<<15) | (2<<10) | (3<<5) | (16<<0);
//	*CR2 |= (1<<15)| (0b111<<12) |(1<<0) | (1<<23);
	//regular
	*CR2 |= (1<<20) | (1<<8);
	*CR2 |= (0b1111<<17);

	uint32_t* SQR1 = (uint32_t*)0x4001242c;
	uint32_t* SQR2 = (uint32_t*)0x40012430;
	uint32_t* SQR3 = (uint32_t*)0x40012434;

	*SQR1 |= (7<<20); //set 8 channel for adc
	*SQR3 |= (1<<0) | (2<<5) | (3<<10) | (4<<15) | (5<<20) | (6<<25);//set pin for channel
	*SQR2 |= (7<<0) | (0<<5);
	*CR2 |= (1<<0);

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
