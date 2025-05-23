

#include "RCC_lib.h"
void Fist_init(crystal_type_t rcc)
{
	uint32_t* SCB_base = (uint32_t*)0xe000ed00;
	uint32_t* SCB_vtor = (uint32_t*)0xE000ED08;
	uint32_t* SCB_AIRCR = (uint32_t*)0xE000ED0C;
	*SCB_vtor = 0x08000000;
	*SCB_AIRCR |= (0x5fa <<16) | ( 3<<8);
	APB1_clk_setup(PWRen);
	APB2_clk_setup(AFIOen);
	uint32_t* AFIO = (uint32_t*) 0x40010004;
	*AFIO |= 0b010<<24;
	RCC_init(rcc);
}
void systick_init()
{
	uint32_t* STCSR = (uint32_t*)0xe000e010;
	uint32_t* STRVR = (uint32_t*)0xe000e014;
	uint32_t* STCVR = (uint32_t*)0xe000e018;
	uint32_t* STCR = (uint32_t*)0xe000e01c;
	uint32_t* SHPR3 = (uint32_t*)0xE000ED20;
}
void RCC_init(crystal_type_t rcc)
{
	uint32_t* RCC_CFGR = (uint32_t*)(RCC_base_adr + 0x04);
	uint32_t* RCC_CIR = (uint32_t*)(RCC_base_adr + 0x08);
	uint32_t* RCC_CR = (uint32_t*)(RCC_base_adr + 0x00);
	uint32_t* FLASH_ACR = (uint32_t*)0x40022000;

	if(rcc == HSE)
	{
		APB2_clk_setup(GPIODen);
		uint32_t* GPIOD_low = (uint32_t)0x40011400;
		*GPIOD_low &= ~(0xff<<0);

		*RCC_CFGR |= (0b01<<0);
		*RCC_CIR |= ((0b1<<11) | (0b1<<18));
		*RCC_CR &= ~(0x01<<0);
		*RCC_CR |= (1<<16);

	}
	else if(rcc = HSI){
		*RCC_CFGR &= ~(0x11<<0);
		*RCC_CIR |= ((0b1<<10) | (0b1<<19));
		*RCC_CR &= ~(1<<16);
		*RCC_CR |= (1<<0);
	}
	else{
		*FLASH_ACR |= 1<<4;
		*FLASH_ACR &= ~(0b111);
		*FLASH_ACR |= 0b010;
		*RCC_CFGR |= (1<<16) | (0b0111<<18);
		*RCC_CR |= 1<<24;
		while(((*RCC_CR >> 25) &1) == 1);
		*RCC_CFGR &= ~(0b11<<0);
		*RCC_CFGR |= (0b10<<0);
		while(((*RCC_CFGR >> 1) & 1) != 1);
		*RCC_CR |= (1<<16);
		while(((*RCC_CR>>17) & 1) == 0);
		set_clock_72Mhz();
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
void set_clock_72Mhz(){
	SystemCoreClock = 72000000;
}
