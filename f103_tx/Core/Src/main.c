
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

void gpio_initqq(){
	// Set alternate function mode
	APB2_clk_setup(GPIOBen);
	APB1_clk_setup(I2C1en);

	uint32_t* GPIOB_LOW = (uint32_t*)0x40010c00;
		*GPIOB_LOW &= ~(0xff << 24);
		*GPIOB_LOW |= (0b11111111 << 24);
	// Set output type to open-drain

}
void i2c1_initq() {
	gpio_initqq();
	uint32_t* CR1 = (uint32_t*)0x40005400;
	uint32_t* CR2 = (uint32_t*)0x40005404;
	uint32_t* CCR = (uint32_t*)0x4000541c;
	uint32_t* TRISE = (uint32_t*)0x40005420;

    *CR1 &= ~(1); // Tắt I2C

    *CR2 = 42; // APB1 = 42MHz
    *CCR = 210;
    *TRISE = 43; // TRISE = (1000ns / (1/42MHz)) + 1

    *CR1 |= (1); // Bật I2C
}

void i2c1_write_cmd(uint8_t cmd) {
    // Start
	uint32_t* CR1 = (uint32_t*)0x40005400;
	uint32_t* SR1 = (uint32_t*)0x40005414;
	uint32_t* SR2 = (uint32_t*)0x40005418;
	uint32_t* DR = (uint32_t*)0x40005410;
	*CR1 |= 1<<8;
	while (!((*SR1>>0) &1));

    // Send address
    *DR = SSD1306_I2C_ADDR << 1; // Write mode
     while (!((*SR1>>1 )& 1));
     int temp;
     temp = *SR2;
     (void)temp;
//     (void)I2C1->SR2;

    // Control byte: Co = 0, D/C = 0 => Command
    while (!((*SR1 >> 7) & 1));
    *DR = 0x00;

    while (!((*SR1 >> 7) & 1));
    *SR1 = cmd;

    while (!((*SR1 >> 7) & 1));
    *SR1 |= 1<<9;
}

void i2c1_write_data(uint8_t data) {
    // Start
	uint32_t* CR1 = (uint32_t*)0x40005400;
	uint32_t* SR1 = (uint32_t*)0x40005414;
	uint32_t* SR2 = (uint32_t*)0x40005418;
	uint32_t* DR = (uint32_t*)0x40005410;
	*CR1 |= 1<<8;
	while (!((*SR1>>0) &1));

    // Address
   *DR = SSD1306_I2C_ADDR << 1;
    while (!((*SR1>> 1)&1));
    int temp;
    temp = *SR2;
    (void)temp;
    // Control byte: Co = 0, D/C = 1 => Data
    while (!((*SR1 >> 7 )& 1));
    *DR = 0x40;

    while (!((*SR1 >> 7) & 1));
    *DR = data;

    while (!((*SR1 >> 7 )& 1));
    *CR1 |= 1<<9;
}
void ssd1306_init() {
    i2c1_initq();

    i2c1_write_cmd(0xAE); // Display OFF
    i2c1_write_cmd(0xD5); i2c1_write_cmd(0x80); // Set clock
    i2c1_write_cmd(0xA8); i2c1_write_cmd(0x3F); // Multiplex
    i2c1_write_cmd(0xD3); i2c1_write_cmd(0x00); // Display offset
    i2c1_write_cmd(0x40); // Start line
    i2c1_write_cmd(0x8D); i2c1_write_cmd(0x14); // Charge pump
    i2c1_write_cmd(0x20); i2c1_write_cmd(0x00); // Horizontal addressing
    i2c1_write_cmd(0xA1); // Segment remap
    i2c1_write_cmd(0xC8); // COM scan dec
    i2c1_write_cmd(0xDA); i2c1_write_cmd(0x12); // COM pins
    i2c1_write_cmd(0x81); i2c1_write_cmd(0xCF); // Contrast
    i2c1_write_cmd(0xD9); i2c1_write_cmd(0xF1); // Pre-charge
    i2c1_write_cmd(0xDB); i2c1_write_cmd(0x40); // VCOMH
    i2c1_write_cmd(0xA4); // Resume display
    i2c1_write_cmd(0xA6); // Normal display
    i2c1_write_cmd(0xAF); // Display ON
}
void ssd1306_clear(void) {
    for (uint8_t page = 0; page < 8; page++) {
        i2c1_write_cmd(0xB0 + page);
        i2c1_write_cmd(0x00);
        i2c1_write_cmd(0x10);
        for (uint8_t col = 0; col < 128; col++) {
            i2c1_write_data(0x00); // Clear
        }
    }
}
void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= 128 || y >= 64) return;

    uint16_t index = x + (y / 8) * 128;

    if (color)
        ssd1306_buffer[index] |= (1 << (y % 8));
    else
        ssd1306_buffer[index] &= ~(1 << (y % 8));
}
void ssd1306_update_screen(void) {
    for (uint8_t page = 0; page < 8; page++) {
        i2c1_write_cmd(0xB0 + page);
        i2c1_write_cmd(0x00);    // lower column
        i2c1_write_cmd(0x10);    // upper column
        for (uint8_t col = 0; col < 128; col++) {
            i2c1_write_data(ssd1306_buffer[page * 128 + col]);
        }
    }
}
void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color) {
    for (uint8_t i = 0; i < w; i++) {
        for (uint8_t j = 0; j < h; j++) {
            ssd1306_draw_pixel(x + i, y + j, color);
        }
    }
}
void test_draw_box() {
    // Xóa màn hình
    memset(ssd1306_buffer, 0x00, sizeof(ssd1306_buffer));

    // Vẽ hình vuông 30x30 tại vị trí (10,10)
    ssd1306_draw_rect(10, 10, 30, 30, 2);

    // Cập nhật màn hình
    ssd1306_update_screen();
}
static void ssd1306_draw_circle_points(uint8_t xc, uint8_t yc, uint8_t x, uint8_t y, uint8_t color) {
    ssd1306_draw_pixel(xc + x, yc + y, color);
    ssd1306_draw_pixel(xc - x, yc + y, color);
    ssd1306_draw_pixel(xc + x, yc - y, color);
    ssd1306_draw_pixel(xc - x, yc - y, color);
    ssd1306_draw_pixel(xc + y, yc + x, color);
    ssd1306_draw_pixel(xc - y, yc + x, color);
    ssd1306_draw_pixel(xc + y, yc - x, color);
    ssd1306_draw_pixel(xc - y, yc - x, color);
}
void ssd1306_draw_circle(uint8_t xc, uint8_t yc, uint8_t r, uint8_t color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        ssd1306_draw_circle_points(xc, yc, x, y, color);
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
void test_draw_circle() {
    memset(ssd1306_buffer, 0x00, sizeof(ssd1306_buffer));
    ssd1306_draw_circle(64, 32, 20, 1); // Hình tròn tâm (64,32) bán kính 20
    ssd1306_update_screen();
}


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
  ssd1306_init();
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
		test_draw_box();
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
