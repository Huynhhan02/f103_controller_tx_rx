/*
 * RCC_lib.h
 *
 *  Created on: Apr 29, 2025
 *      Author: User
 */

#ifndef RCC_LIB_RCC_LIB_H_
#define RCC_LIB_RCC_LIB_H_

#include "stdint.h"
#define RCC_base_adr 0x40021000

typedef enum{
	HSI,
	HSE,
	 PLL,
}crystal_type_t;

typedef enum{
	DMA1en = 0,
	DMA2en


}RCC_AHB1_bit;

typedef enum{
	TIM2en,
	TIM3en,
	TIM4en,
	TIM5en,
	TIM6en,
	TIM7en,
	WWDGen = 11,
	SPI2en = 14,
	SPI3en,
	UART2en = 17,
	UART3en,
	UART4en,
	UART5en,
	I2C1en,
	I2C2en,
	CAN1en = 25,
	CAN2en,
	PWRen = 28
}RCC_APB1_bit;

typedef enum{
	AFIOen = 0,
	GPIOAen = 2,
	GPIOBen,
	GPIOCen,
	GPIODen,
	GPIOEen,
	ADC1en = 9,
	ADC2en,
	UART1en = 14
}RCC_APB2_bit;

extern uint32_t SystemCoreClock;

void Fist_init(crystal_type_t rcc);
void RCC_init(crystal_type_t rcc);
void AHB1_clk_setup(RCC_AHB1_bit AHB1_bit);
void APB1_clk_setup(RCC_APB1_bit APB1_bit);
void APB2_clk_setup(RCC_APB2_bit APB2_bit);
void set_clock_72Mhz(void);

#endif /* RCC_LIB_RCC_LIB_H_ */
