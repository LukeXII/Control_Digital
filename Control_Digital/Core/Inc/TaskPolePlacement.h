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

#define	LOOP_SAMPLING_TIME	8.0
#define SQUARE_VALUE_1V		1241
#define SQUARE_VALUE_0V		1
#define ADC_RESOLUTION		3.3/4095.0
//#define K1					0.4778
//#define K2					0.1
//#define Kf					1.61


void TaskPolePlacement(void * argument);

#endif
