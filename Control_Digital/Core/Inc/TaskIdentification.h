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

#define WAVEFORM_DEBUG	0

extern DAC_HandleTypeDef hdac;

#define	LOOP_SAMPLE_TIME	50
#define DAC_REFERENCE_VALUE_LOW		1427
#define DAC_REFERENCE_VALUE_HIGH	2668

void TaskIdentification(void * argument);
void receiveData (float * buffer);
void console_print (float * buffer);

#endif /* INC_TASKIDENTIFICATION_H_ */
