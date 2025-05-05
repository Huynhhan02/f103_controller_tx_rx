
#include "main.h"
#include "string.h"

#include "RCC_lib.h"
#include "gpio_lib.h"
#include "uart1_lib.h"
#include "DMA_lib.h"
#include "timer_lib.h"
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);

#define led_on (led_control(13,1))
#define led_off (led_control(13,0))

char data[20];
int indx = 0;
char uart_buff[20];

static char connect_flag = 0;

void connect_handler()
{
	int time_out = 0;
	while(1)
	{
		toggle_led(13);
		delay(200);
		send_data("hallo", 5);
		if(strcmp(uart_buff,"ok\r\n") == 0)
		{
			strcpy(uart_buff,"");
			send_data("connect", 7);
			connect_flag = 0;
			break;
		}
		if(time_out++ >50){
			send_data("fail", 4);
			connect_flag = 0;
			break;
		}
	}

}
void EXTI0_IRQHandler()
{
	delay(1000);
	if((int)button_read(0) == 0)
	{
		connect_flag = 1;
	}
	uint32_t* EXTI_PR =(uint32_t*) 0x40010414;
	*EXTI_PR |= (0x01<<0);
}
void USART1_IRQHandler()
{
	data[indx] = recv_byte();
	if(data[indx++] == '\n')
	{
		indx = 0;
		strcpy(uart_buff,data);
		strcpy(data,"");
		if(strcmp(uart_buff,"han\r\n")==0)
		{
			send_data("hello", 5);
			strcpy(uart_buff,"");
		}

	}
}
int main(void)
{


  HAL_Init();
  RCC_init(HSI);
//  SystemClock_Config();
  APB1_clk_setup(UART2en);
  APB2_clk_setup(GPIOCen);
  APB2_clk_setup(GPIOAen);
  APB1_clk_setup(TIM4en);
  uart1_init_interrupt();

  gpio_pin_t pin = {
		  .config_output = output_push_pull,
		  .mode = output_10Mhz,
		  .pin = 13,
		  .port = PORTC,
  };
  gpio_init(&pin);
  button_init();
  timer_init();
//  uint32_t* NVIC_IPR37 = 0xe000e494;
//  *NVIC_IPR37 = 13;
//  uint32_t* NVIC_IPR6 = 0xe000e418;
//  *NVIC_IPR6 = 40;

  while (1)
  {
	  if(connect_flag)
	  {
		  connect_handler();
	  }
//	 toggle_led(13);
//	 delay(1000);
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
//	  led_on;
//	  HAL_Delay(100);
//	  led_off;
//	  HAL_Delay(100);
//	  send_data("hello\r\n",9);

//	  a = recv_byte();
  }
  /* USER CODE END 3 */
}

