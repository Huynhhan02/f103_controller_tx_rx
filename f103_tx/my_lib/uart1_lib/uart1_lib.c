/*
 * uart_lib.c
 *
 *  Created on: May 1, 2025
 *      Author: deffen
 */

#include "uart1_lib.h"


void uart1_init()
{
	//pb6-tx,pb7-rx
	uint32_t* GPIOA_AFH = (uint32_t*)0x40010804;
	*GPIOA_AFH &= ~(0b11111111<<4);
	*GPIOA_AFH |= (0b10111011<<4);



//	uint32_t* AFIO_MAPR = (uint32_t*)0x40010004;
//	*AFIO_MAPR |= (1<<2);

	//set uart baudrate = 9600
	uint32_t* UART1_BRR = (uint32_t*)0x40013808;
	*UART1_BRR = ((52<<4) | (1<<0));
	uint32_t* UART1_CR1 = (uint32_t*)0x4001380c;
	*UART1_CR1 |= ((1<<13) | (1<<2) | (1<<3));



}


void send_byte(char data)
{
	uint32_t* USART2_SR = (uint32_t*)0x40013800;
	uint32_t* USART2_DR = (uint32_t*)0x40013804;

	while(((*USART2_SR>>7) &1) != 1);
	*USART2_DR = data;
	while(((*USART2_SR>>6) &1) != 0);
}
void send_data(char* data, int data_leght)
{
	for(int i =0; i< data_leght; i++)
	{
		send_byte(data[i]);
	}
}
