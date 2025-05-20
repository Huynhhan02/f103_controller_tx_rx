/*
 * i2c_lib.c
 *
 *  Created on: May 18, 2025
 *      Author: deffen
 */
#include "i2c_lib.h"

void i2c_init()
{
	//config gpiob to altenate function
	//PB6 SCK PB7 SCL
	APB2_clk_setup(GPIOBen);
	uint32_t* GPIOB_LOW = (uint32_t*)0x40010c00;
	*GPIOB_LOW &= ~(0xff << 24);
	*GPIOB_LOW |= (0b11111111 << 24);

	APB1_clk_setup(I2C1en);
	//i2c config
	uint32_t* CR1 = (uint32_t*)0x40005400;
	uint32_t* CR2 = (uint32_t*)0x40005404;
	*CR2 |= 8;
	uint32_t* CCR = (uint32_t*)0x4000541c;
	*CCR |= 80;

	*CR1 |= 1<<0;
}

char read_i2c(uint8_t adress, uint8_t registor)
{
	uint32_t* CR1 = (uint32_t*)0x40005400;
	uint32_t* SR1 = (uint32_t*)0x40005414;
	uint32_t* SR2 = (uint32_t*)0x40005418;
	uint32_t* DR = (uint32_t*)0x40005410;

	uint8_t adr = 0b11010000;

	while ((*SR2 >> 1) & 1 == 1);
	*CR1 |= 1<<8; //start bit
	while(((*SR1 >>0) & 1) != 1);
	*DR = adr | 0;

	while(((*SR1 >>1) & 1) != 1);
	uint32_t temp = *SR2;
	(void) temp;
	*DR = registor;
	while(((*SR1 >> 2) & 1) != 1);
	while(((*SR1 >> 10) & 1) == 1);

	*CR1 |= (1<<8);
	while(((*SR1 >>0 ) & 1) != 1);
	*DR = adr | 1;
	while((*SR1 >> 1 ) & 1 != 1);
	temp = *SR2;
	while((*SR1 >>6) & 1 != 1);
	uint8_t data = *DR;
	*CR1 |= (0b1 << 9);
	return data;
}
