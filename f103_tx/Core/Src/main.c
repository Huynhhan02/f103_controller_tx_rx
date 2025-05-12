
#include "main.h"
#include "string.h"
#include "cmsis_os.h"


#include "RCC_lib.h"
#include "gpio_lib.h"
#include "uart1_lib.h"
#include "DMA_lib.h"
#include "timer_lib.h"
#include "data_handle.h"
#include "adc_lib.h"
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};


#define led_on (led_control(13,1))
#define led_off (led_control(13,0))


void StartDefaultTask(void *argument);
void StartTask02(void *argument);


char data[20];
char aaa[4];
int indx = 0;
char uart_buff[];
char alarm[10];
uint32_t temp1 = 767574684;
uint16_t x,y,z,g;

static char connect_flag = 0;
typedef struct test{
		int test1;
		int test2;
}test_type_t;

void EXTI0_IRQHandler()
{
	osDelay(1000);
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
//		send_data(uart_buff, strlen(data));
//		memset(uart_buff,0,strlen(uart_buff));
		memset(data,0,strlen(data));
		if(strcmp(uart_buff,"han\r\n")==0)
		{
			send_data("hello", 5);
			memset(uart_buff,0,strlen(uart_buff));
		}

	}
}
int main(void)
{

  HAL_Init();
  RCC_init(HSI);
  osKernelInitialize();

//  SystemClock_Config();
  APB2_clk_setup(GPIOCen);
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
  adc_init();
  DMA_ADC_init(&x);
  convert_int_to_4char(aaa, temp1);
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);
  strcpy(alarm,"ngaancuc");
  osKernelStart();

  /* USER CODE END 3 */
}


void StartDefaultTask(void *argument)
{
	while(1)
	{
		if(connect_flag)
		{
		 connect_handler(&connect_flag,uart_buff);
		}
		osDelay(1);
	}
}
void StartTask02(void *argument)
{
	while(1)
	{

		send_data(alarm,strlen(alarm));

		osDelay(100);
	}
}
