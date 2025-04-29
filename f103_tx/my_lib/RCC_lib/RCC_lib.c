

#include "RCC_lib.h"
void RCC_init(crystal_type_t rcc)
{
	uint8_t temp = 0;
	uint32_t* RCC_CFGR = (uint32_t*)(RCC_base_adr + 0x04);
	uint32_t* RCC_CIR = (uint32_t*)(RCC_base_adr + 0x08);
	if(rcc == HSE)
	{
		temp = 16;
		*RCC_CFGR |= (0b01<<0);
		*RCC_CIR |= ((0b1<<11) | (0b1<<18));
	}
	else{
		temp =  0;
		*RCC_CFGR &= ~(0x11<<0);
		*RCC_CIR |= ((0b1<<10) | (0b1<<19));
	}
	uint32_t* RCC_CR = (uint32_t*)(RCC_base_adr + 0x00);
	*RCC_CR |= (1<<temp);
	if(rcc == HSE)
	{
			temp = 16;
			*RCC_CFGR |= (0b01<<0);
			*RCC_CIR |= ((0b1<<11) | (0b1<<18));
	}
	else{
		temp =  0;
			*RCC_CFGR &= ~(0x11<<0);
			*RCC_CIR |= ((0b1<<10) | (0b1<<19));
		}
	APB1_clk_setup(PWRen);
}

void AHB1_clk_setup(RCC_AHB1_bit AHB1_bit)
{
	uint32_t* RCC_AHB1 = (uint32_t*)(RCC_base_adr + 0x14);
	*RCC_AHB1 |= (0x01<< AHB1_bit ); // GPIOD_clk_enable
}

void APB1_clk_setup(RCC_APB1_bit APB1_bit)
{
	uint32_t* RCC_APB1 = (uint32_t*)(RCC_base_adr + 0x1c);
	*RCC_APB1 |= (0x01<< APB1_bit ); // GPIOD_clk_enable

}


void APB2_clk_setup(RCC_APB2_bit APB2_bit)
{
	uint32_t* RCC_APB2 = (uint32_t*)(RCC_base_adr + 0x18);
	*RCC_APB2 |= (0x01<< APB2_bit ); // GPIOD_clk_enable

}
