/*
 * TaskPolePlacement.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskPolePlacement.h"

void TaskPolePlacement(void * argument)
{
	uint32_t xLastWakeTime, outputSample;
	uint16_t setpoint = SQUARE_VALUE_2V;
	float controlSignal, res = 3.3/4095.0;

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SQUARE_VALUE_1V);
	vTaskDelay(1000);

	vPrintString("start--------");
	vPrintNewLine();

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{


		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		outputSample = HAL_ADC_GetValue(&hadc1);

		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		outputSample = HAL_ADC_GetValue(&hadc1);



		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)((float)controlSignal/res) );

		vPrintNumber(setpoint);
		vPrintStringAndNumber(",", outputSample);
		vPrintStringAndNumber(",", (uint32_t)((float)controlSignal/res));
		vPrintNewLine();

		vTaskDelayUntil(&xLastWakeTime, LOOP_SAMPLING_TIME);

	}

}
