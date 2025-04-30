/*
 * gpio_lib.h
 *
 *  Created on: Apr 30, 2025
 *      Author: deffen
 */

#ifndef GPIO_LIB_GPIO_LIB_H_
#define GPIO_LIB_GPIO_LIB_H_

#include "stdio.h"
#include "stdint.h"

#define GPIOA_base_adr 		0x40010800
#define GPIOB_base_adr 		0x40010C00
#define GPIOC_base_adr 		0x40011000

typedef enum{
	input,
	output_10Mhz,
	output_2Mhz,
	output_50Mhz
}gpio_mode_t;

typedef enum{
	analog_mode,
	floating_input,
	pullup_pulldown,
}configure_mode_input_t;
typedef enum{
	output_push_pull,
	output_open_drain,
	output_atlfnc_push_pull,
	output_atlfnc_open_drain
}configure_mode_output_t;
typedef enum{
	PORTA,
	PORTB,
	PORTC
}port_t;


typedef struct gpio_pin{
	int port;
	int pin;
	gpio_mode_t mode;
	configure_mode_input_t config_input;
	configure_mode_output_t config_output;
}gpio_pin_t;
//typedef gpio_pin gpio_pin_t;

void gpio_init(gpio_pin_t *pin);
#endif /* GPIO_LIB_GPIO_LIB_H_ */
