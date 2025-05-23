#include "string.h"
#include "cmsis_os.h"


#include "RCC_lib.h"
#include "gpio_lib.h"
#include "uart1_lib.h"
#include "DMA_lib.h"
#include "timer_lib.h"
#include "data_handle.h"
#include "adc_lib.h"

char data[20];
char aaa[4];
int indx = 0;

uint32_t temp1;
uint16_t y,g;
uint8_t RECEIVE_CHANNEL[8];
uint8_t i2c_buff[10];
char CH1[2];
char dataCH1_CH8[8];
static char connect_flag = 0;
int first_uart_flag = 0;


osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
void StartDefaultTask(void *argument);


void USART1_IRQHandler()
{

	data[indx] = recv_byte();

	if(data[indx++] == '\n')
	{
		indx = 0;
//		strcpy(uart_buff,data);
		memset(data,0,strlen(data));
	}
	if(indx>20)
		indx = 0;
}
int main(void)
{
 	Fist_init(PLL);
	timer3_pwm_init();
	timer4_pwm_init();
	uart1_init_interrupt();
	led_init();
	timer2_init();
	y = 0;
	osKernelInitialize();

	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	osKernelStart();

}


void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  uint32_t* CCR1 = (uint32_t*)0x40000434;
	  *CCR1 = y++;
	  if(y>100)
		  y= 0;
		osDelay(200);
  }
  /* USER CODE END 5 */
}
