
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
//#include "i2c_li.h"
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
uint8_t ssd1306_buffer[1024]; // 128x64 / 8
#define SSD1306_I2C_ADDR  0x3C
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t rxConnectHandle;
const osThreadAttr_t rxConnect_attributes = {
  .name = "rxConnect",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};


#define led_on (led_control(13,1))
#define led_off (led_control(13,0))


void StartDefaultTask(void *argument);
void rxConnectTask(void *argument);

char data[20];
char aaa[4];
int indx = 0;
char uart_buff[];
char alarm[10];
uint32_t temp1;
uint16_t y,g;
uint8_t SEND_CHANNEL[8];
uint16_t ADC_read_buff[8];
uint8_t i2c_buff[10];
char CH1[2];
char dataCH1_CH8[8];
static char connect_flag = 0;
int first_uart_flag = 0;


void EXTI9_5_IRQHandler()
{
	//delay(3000);
	if((int)button_read(8) == 0)
	{
		connect_flag = 1;
		uint32_t* NVIC_ISER1 = 0xE000E104;
		*NVIC_ISER1 |= (0b1<<5);
	}

	uint32_t* EXTI_PR =(uint32_t*) 0x40010414;
	*EXTI_PR |= (0x01<<8);
}

void USART1_IRQHandler()
{

	data[indx] = recv_byte();

	if(data[indx++] == '\n')
	{
		strcpy(uart_buff,"");
		indx = 0;
		strcpy(uart_buff,data);
		memset(data,0,strlen(data));
	}
	if(indx>20)
		indx = 0;
}
int main(void)
{
     HAL_Init();
  RCC_init(PLL);
  osKernelInitialize();
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
//  i2c1_initq()

  adc_init();
  connect_handler(&connect_flag, uart_buff);
  DMA_ADC_init((uint32_t)ADC_read_buff);
//  uint32_t* NVIC_IPR37 = (uint32_t*) 0xe000e494;
//  *NVIC_IPR37 = 13;
  //connect_handle = osThreadNew(connect_handle_task, NULL, &connect_handle_attributes);
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  rxConnectHandle = osThreadNew(rxConnectTask, NULL, &rxConnect_attributes);
  osKernelStart();
//  while(1)
//  	{
////  		convert_uint16_to_2char(CH1,ADC_read_buff[0]);
//  		g = read_regular_CH1();
////  		z = MAP(convert_2char_to_uint16(CH1), 0, 4095, 0, 180);
//  		send_data(&g, 1);
//
//  		if(connect_flag == 1)
//  			connect_handler(&connect_flag, uart_buff);
//
//  		delay(200);
//
//  	}
  /* USER CODE END 3 */
}



void StartDefaultTask(void *argument)
{
	while(1)
	{
//		convert_uint16_to_2char(CH1,ADC_read_buff[0]);
//		SEND_CHANNEL[0] = MAP(ADC_read_buff[0], 0, 4095, 0, 180);
//		convertADC_to_sendchanel(SEND_CHANNEL, ADC_read_buff);
//		send_data(&SEND_CHANNEL, 2);
//		g = read_regular_CH1();
//		test_draw_box();
//		i2c_buff[0] = read_i2c(0x68, 0x75);
		osDelay(500);


	}
}
void rxConnectTask(void *argument)
{
	while(1)
 	{
		if(connect_flag)
		{
			osThreadSuspend(defaultTaskHandle);
			connect_handler(&connect_flag, uart_buff);
			osThreadResume(defaultTaskHandle);
		}

		osDelay(1000);
	}
}
