/*
 * gpio_lib.c
 *
 *  Created on: Apr 30, 2025
 *      Author: deffen
 */


#include "gpio_lib.h"


void gpio_init(gpio_pin_t *pin)
{
	uint32_t base = 0x40011000;
//	switch(pin->port)
//	{
//		case(PORTA):
//			base = (uint32_t*)GPIOA_base_adr;
//			break;
//		case(PORTB):
//			base = (uint32_t*)GPIOB_base_adr;
//			break;
//		case(PORTC):
//			base = (uint32_t*)GPIOC_base_adr;
//	}
	uint32_t* GPIO_CRL = (uint32_t*)(base + 0x00);
	uint32_t* GPIO_CRH = (uint32_t*)base + 0x04;
//	if(pin->mode == input)
//	{
//		if(pin->pin <=7)
//		{
//			*GPIO_CRL |= (pin->mode << (pin->pin * 4));
//			*GPIO_CRL |= (pin->config_input << ((pin->pin * 4)+2));
//		}
//		else{
//			*GPIO_CRH |= (pin->mode << ((pin->pin * 4) - 32));
//			*GPIO_CRH |= (pin->config_input << (((pin->pin * 4)+2) - 32 ));
//		}
//	}
//	else{
//		if(pin->pin <=7)
//		{
//			*GPIO_CRL |= (pin->mode << (pin->pin * 4));
//			*GPIO_CRL |= (pin->config_output << ((pin->pin * 4)+2));
//		}
//		else{
			*GPIO_CRH |= (1 <<20);
			*GPIO_CRH |= (0 << 22);
//		}
//	}

}
