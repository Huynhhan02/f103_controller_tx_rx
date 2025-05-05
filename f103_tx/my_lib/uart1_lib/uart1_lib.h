/*
 * uart1_lib.h
 *
 *  Created on: May 1, 2025
 *      Author: deffen
 */

#ifndef UART1_LIB_UART1_LIB_H_
#define UART1_LIB_UART1_LIB_H_

#include "stdint.h"
#include "gpio_lib.h"
#include "RCC_lib.h"

void uart1_init();
void send_byte(char data);
void send_data(char* data, int data_leght);
void uart1_init_interrupt();

#endif /* UART1_LIB_UART1_LIB_H_ */
