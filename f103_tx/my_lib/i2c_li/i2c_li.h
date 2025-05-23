/*
 * i2c_li.h
 *
 *  Created on: May 22, 2025
 *      Author: deffen
 */

#ifndef I2C_LI_I2C_LI_H_
#define I2C_LI_I2C_LI_H_

#include "RCC_lib.h"
#include "stdint.h"
#include "string.h"

//uint8_t ssd1306_buffer[1024]; // 128x64 / 8
//#define SSD1306_I2C_ADDR  0x3C
void ssd1306_init();
void test_draw_box();


#endif /* I2C_LI_I2C_LI_H_ */
