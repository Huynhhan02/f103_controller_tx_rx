/*
 * data_handle.c
 *
 *  Created on: May 7, 2025
 *      Author: deffen
 */


#include "data_handle.h"


void convert_int_to_4char(char* a,uint32_t num)
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

void connect_handler(char* flag,char* uart_buffer)
{
	int time_out = 0;
	while(1)
	{
		toggle_led(13);
		delay(300);
		send_data("hallo", 5);
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
