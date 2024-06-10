/*
 * TaskPolePlacement.h
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#ifndef INC_TASKPOLEPLACEMENT_H_
#define INC_TASKPOLEPLACEMENT_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dac.h"
#include "usart.h"

extern DAC_HandleTypeDef hdac;

#define	LOOP_SAMPLING_TIME_PP	8
#define SQUARE_VALUE_1V			1241
#define SQUARE_VALUE_0V			1
#define ADC_RESOLUTION			3.3/4095.0
#define K1_PP					-0.394			// 0.51
#define K2_PP					0.412			// 0.283
#define Kf_PP					1.018			// 1.793

void TaskPolePlacement(void * argument);

#endif
