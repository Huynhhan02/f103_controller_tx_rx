/*
 * data_handle.c
 *
 *  Created on: May 7, 2025
 *      Author: deffen
 */


#include "data_handle.h"


void convert_uint32_to_4char(char* a,uint32_t num)
{
	a[3] = (num>>24) & 0xFF;
	a[2] = (num>>16) & 0xFF;
	a[1] = (num>>8) & 0xFF;
	a[0] = num & 0xFF;

}
uint32_t convert_4char_to_uint32(char* a)
{
	return  *(int *)a;
}

void convert_uint16_to_2char(char* a,uint32_t num)
{
	a[1] = (num>>8) & 0xFF;
	a[0] = num & 0xFF;

}
uint16_t convert_2char_to_uint16(char* a)
{
	return  *(int *)a;
}
uint16_t MAP(uint16_t u16DataIn, uint16_t DATA_IN_MIN, uint16_t DATA_IN_MAX, uint16_t DATA_OUT_MIN, uint16_t DATA_OUT_MAX)
{
    return ((((u16DataIn - DATA_IN_MIN)*(DATA_OUT_MAX - DATA_OUT_MIN))/(DATA_IN_MAX - DATA_IN_MIN)) + DATA_OUT_MIN);
}


void connect_handler(char* flag,char* uart_buffer)
{
	int time_out = 0;
	while(1)
	{
		toggle_led(13);
		delay(3000);
		char* msg = "request\r\n";
		send_data(msg, strlen(msg));
		if(strcmp(uart_buffer,"ok\r\n") == 0)
		{
			send_data("connect", 7);

//				for(int i;i < sizeof(uart_buffer);i++)
//				{
//					uart_buffer[i] = 0;
//				}
			memset(uart_buffer,0,strlen(uart_buffer));

			*flag = 0;
			break;
		}
		if(time_out++ >50){
			send_data("fail", 4);
			*flag = 0;
			break;
		}
	}

}


void convertADC_to_sendchanel(uint8_t channel[], uint16_t ADC_buff[])
{
	for(int i = 0; i<8 ;i++)
	{
		channel[i] = MAP(ADC_buff[i], 0, 4095, 0, 100);
	}
}
