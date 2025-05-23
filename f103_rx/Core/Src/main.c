#include "string.h"
#include "cmsis_os.h"


#include "RCC_lib.h"
#include "gpio_lib.h"
#include "uart1_lib.h"
#include "DMA_lib.h"
#include "timer_lib.h"
#include "data_handle.h"
#include "adc_lib.h"

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
void StartDefaultTask(void *argument);

int main(void)
{
 	Fist_init(PLL);
	APB2_clk_setup(GPIOBen);
	uart1_init_interrupt();
	led_init();
	timer_init();
	osKernelInitialize();

	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	osKernelStart();

//while(1)
//{
//	led_control(12,0);
//	delay(100);
//	led_control(12,1);
//	delay(100);
//
//}
}


void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  	led_control(12,0);
	  	osDelay(100);
	  	led_control(12,1);
	  	osDelay(100);
  }
  /* USER CODE END 5 */
}
