/*
 * uart_lib.c
 *
 *  Created on: May 1, 2025
 *      Author: deffen
 */

#include "uart1_lib.h"


void uart1_init()
{
	 APB2_clk_setup(UART1en);

	//PA9-tx,PA10-rx
	uint32_t* GPIOA_AFH = (uint32_t*)0x40010804;
	*GPIOA_AFH &= ~(0b11111111<<4);
	*GPIOA_AFH |= (0b01001011<<4);


	//set uart baudrate = 9600
	uint32_t* UART1_BRR = (uint32_t*)0x40013808;
	*UART1_BRR = ((52<<4) | (1<<0));
	uint32_t* UART1_CR1 = (uint32_t*)0x4001380c;
	*UART1_CR1 |= ((1<<13) | (1<<2) | (1<<3) | (1<<8));
	uint32_t* UART1_CR3 = (uint32_t*)0x40013814;
	*UART1_CR3 |= 1<<6 ;

}

void uart2_init()
{
	//PA2-tx,PA3-rx
	uint32_t* GPIOA_AFL = (uint32_t*)0x40010800;
	*GPIOA_AFL &= ~(0b11111111<<8);
	*GPIOA_AFL |= (0b01001011<<8);


	//set uart baudrate = 9600
	uint32_t* UART1_BRR = (uint32_t*)0x40004408;
	*UART1_BRR = ((52<<4) | (1<<0));
	uint32_t* UART1_CR1 = (uint32_t*)0x4000440c;
	*UART1_CR1 |= ((1<<13) | (1<<2) | (1<<3));
	uint32_t* UART1_CR3 = (uint32_t*)0x40004414;
	*UART1_CR3 |= (1<<6) | (1<<0);
	uint32_t* NVIC_ISER1 = 0xE000E104;
	*NVIC_ISER1 |= (0b111<<5);
}

void send_byte(char data)
{
	uint32_t* USART_SR = (uint32_t*)0x40013800;
	uint32_t* USART_DR = (uint32_t*)0x40013804;

	while(((*USART_SR>>7) &1) != 1);
	*USART_DR = data;
	while(((*USART_SR>>6) &1) != 0);
}
void send_byte_uart2(char data)
{
	uint32_t* USART_SR = (uint32_t*)0x40004400;
	uint32_t* USART_DR = (uint32_t*)0x40004404;

	while(((*USART_SR>>7) &1) != 1);
	*USART_DR = data;
	while(((*USART_SR>>6) &1) != 0);
}
void send_data(char* data, int data_leght)
{
	for(int i =0; i< data_leght; i++)
	{
		send_byte(data[i]);
	}
}
void send_data_uart2(char* data, int data_leght)
{
	for(int i =0; i< data_leght; i++)
	{
		send_byte_uart2(data[i]);
	}
}
char recv_byte()
{
	uint32_t* USART2_SR = (uint32_t*)0x40013800;
	uint32_t* USART2_DR = (uint32_t*)0x40013804;

	while(((*USART2_SR>>5)&1)==0);
	char data = * USART2_DR;
	return data;
}
