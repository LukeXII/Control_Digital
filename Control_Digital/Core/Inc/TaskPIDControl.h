/*
 * TaskPIDControl.h
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#ifndef INC_TASKPIDCONTROL_H_
#define INC_TASKPIDCONTROL_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dac.h"
#include "usart.h"

extern DAC_HandleTypeDef hdac;

#define	LOOP_SAMPLING_TIME	8.0
#define SQUARE_VALUE_1V		1241
#define SQUARE_VALUE_2V		2482
#define RESOLUTION_LSB		3.3/4095.0

void TaskPIDControl(void * argument);

#endif
