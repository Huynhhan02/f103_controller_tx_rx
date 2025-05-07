/*
 * data_handle.h
 *
 *  Created on: May 7, 2025
 *      Author: deffen
 */

#ifndef DATA_HANDLE_DATA_HANDLE_H_
#define DATA_HANDLE_DATA_HANDLE_H_

#include "stdint.h"
#include "string.h"
#include "uart1_lib.h"
#include "gpio_lib.h"
void convert_int_to_4char(char* a,uint32_t num);
uint32_t convert_4char_to_uint32(char*);
void connect_handler(char* flag,char* uart_buffer);

#endif /* DATA_HANDLE_DATA_HANDLE_H_ */
