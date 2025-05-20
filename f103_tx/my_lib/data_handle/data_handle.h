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
void convert_uint32_to_4char(char* a,uint32_t num);
uint32_t convert_4char_to_uint32(char*);
void convert_uint16_to_2char(char* a,uint32_t num);
uint16_t convert_2char_to_uint16(char* a);
uint16_t MAP(uint16_t u16DataIn, uint16_t DATA_IN_MIN, uint16_t DATA_IN_MAX, uint16_t DATA_OUT_MIN, uint16_t DATA_OUT_MAX);

void connect_handler(char* flag,char* uart_buffer);

#endif /* DATA_HANDLE_DATA_HANDLE_H_ */
