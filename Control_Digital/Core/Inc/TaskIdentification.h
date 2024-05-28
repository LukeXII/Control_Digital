/*
 * TaskIdentification.h
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#ifndef INC_TASKIDENTIFICATION_H_
#define INC_TASKIDENTIFICATION_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dac.h"
#include "usart.h"

extern DAC_HandleTypeDef hdac;

#define	LOOP_SAMPLE_TIME	50
#define SQUARE_VALUE_1V		1241
#define SQUARE_VALUE_2V		2482

void TaskIdentification(void * argument);

#endif /* INC_TASKIDENTIFICATION_H_ */
