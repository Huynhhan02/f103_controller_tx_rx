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
