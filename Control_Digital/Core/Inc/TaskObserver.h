/*
 * TaskObserver.h
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#ifndef INC_TASKOBSERVER_H_
#define INC_TASKOBSERVER_H_

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
#define K1					0.4778
#define K2					0.1
#define Kf					1.578
#define L1					0.298
#define L2					0.713
#define A11					0.354
#define A12					0.154
#define A21					0.154
#define A22					0.769
#define B1					0.492
#define B2					0.077
#define C1					0
#define C2					1

void TaskObserver(void * argument);

#endif
