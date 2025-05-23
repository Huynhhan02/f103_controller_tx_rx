/*
 * gpio_lib.c
 *
 *  Created on: Apr 30, 2025
 *      Author: deffen
 */


#include "gpio_lib.h"


void gpio_init(gpio_pin_t *pin)
{
	APB2_clk_setup(GPIOCen);
	  APB2_clk_setup(GPIOAen);
	  APB2_clk_setup(AFIOen);
	uint32_t base = 0;
	switch(pin->port)
	{
		case(PORTA):
			base = GPIOA_base_adr;
			break;
		case(PORTB):
			base = GPIOB_base_adr;
			break;
		case(PORTC):
			base = GPIOC_base_adr;
			break;
	}
	uint32_t* GPIO_CRL = (uint32_t*)(base + 0x00);
	uint32_t* GPIO_CRH = (uint32_t*)(base + 0x04);
	if(pin->mode == input)
	{
		if(pin->pin <=7)
		{
			*GPIO_CRL |= (pin->mode << (pin->pin * 4));
			if(pin->config_input == analog_mode)
				*GPIO_CRL &= ~(0b11 << ((pin->pin * 4)+2));
			else
				*GPIO_CRL |= (pin->config_input << ((pin->pin * 4)+2 ));
		}
		else{
			*GPIO_CRH |= (pin->mode << ((pin->pin * 4) - 32));
			if(pin->config_input == analog_mode)
				*GPIO_CRH &= ~(0b11 << (((pin->pin * 4)+2) - 32 ));
			else
				*GPIO_CRH |= (pin->config_input << (((pin->pin * 4)+2) - 32 ));
		}
	}
	else{
		if(pin->pin <=7)
		{

			*GPIO_CRL |= (pin->mode << (pin->pin * 4));
			if(pin->config_output == output_push_pull)
				*GPIO_CRL &= ~(0b11 << ((pin->pin * 4)+2));
			else
				*GPIO_CRL |= (pin->config_output << ((pin->pin * 4)+2 ));
		}
		else{
			*GPIO_CRH |= (pin->mode << ((pin->pin * 4) - 32));
			if(pin->config_output == output_push_pull)
				*GPIO_CRH &= ~(0b11 << (((pin->pin * 4)+2) - 32 ));
			else
				*GPIO_CRH |= (pin->config_input << (((pin->pin * 4)+2) - 32 ));
		}
	}

}
void led_init()
{
	  APB2_clk_setup(GPIOBen);

	uint32_t* CRH = (uint32_t*) 0x40010c04;
	*CRH &= ~(0b1111 << 16);
	*CRH |= (0b0001<<16);

}

void button_init()
{
	APB2_clk_setup(GPIOAen);

	uint32_t* GPIOB_CRH = (uint32_t*)0x40010804;
	*GPIOB_CRH &= ~(0b1111<<0);

	*GPIOB_CRH |= (0b1000<<0);
	uint32_t* GPIOB_ODR = (uint32_t*)0x4001080c;
	*GPIOB_ODR |= (1<<8);
	uint32_t* EXTI_IMR = (uint32_t*)0x40010400;
	*EXTI_IMR |= (1<<8);
	uint32_t* EXTI_RTSR = (uint32_t*)0x40010408;
	*EXTI_RTSR |= 1<<8;

	uint32_t* NVIC_ISER0 = 0xe000e100;
	 *NVIC_ISER0 |= (0b1<<23);

}

void led_control(int led, int led_state)
{
	uint32_t* GPIOC_ODR = (uint32_t*)0x40010c0c;
	if(led_state == 1){
		*GPIOC_ODR |= (0b1<<led);
	}
	else{
		*GPIOC_ODR &= ~(0b1<<led);
	}
}

void toggle_led(int led)
{
	uint32_t* GPIOD_ODR = (uint32_t*)0x40010c0c;
	if(((*GPIOD_ODR>>led)& 0x01) == 1)
		led_control(led, 0);
	else
		led_control(led, 1);
}
void toggle_led_3(int led){
	int i = 0;
	while (i++<5){
		toggle_led(led);
		delay(100);
	}
}
char button_read(int button_number)
{
	uint32_t* GPIOA_IDR = (uint32_t*) 0x40010808;
	return (*GPIOA_IDR>>button_number) & 0x01;
}
