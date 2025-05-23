/*
 * adc_lib.h
 *
 *  Created on: May 11, 2025
 *      Author: deffen
 */

#ifndef ADC_LIB_ADC_LIB_H_
#define ADC_LIB_ADC_LIB_H_

#include "RCC_lib.h"
#include "stdint.h"

void adc_init();
uint16_t read_adc_channel1();
uint16_t read_adc_channel2();
uint16_t read_adc_channel3();
uint16_t read_adc_channel4();

#endif /* ADC_LIB_ADC_LIB_H_ */
