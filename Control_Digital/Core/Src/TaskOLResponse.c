/*
 * TaskIdentification.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskOLResponse.h"

void TaskOLResponse(void * argument)
{
	uint32_t xLastWakeTime, outputSample;
	uint16_t squareValue = SQUARE_VALUE_1V;
	uint8_t samplesCounter = 0;

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, squareValue);
	vTaskDelay(1000);

	vPrintString("start--------");
	vPrintNewLine();

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{

		if(samplesCounter == 100)
		{
			(squareValue == SQUARE_VALUE_1V) ? (squareValue = SQUARE_VALUE_2V) : (squareValue = SQUARE_VALUE_1V);
			samplesCounter = 0;
		}

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, squareValue);

		HAL_ADC_Start(&hadc1);
		outputSample = HAL_ADC_GetValue(&hadc1);

		vPrintNumber(squareValue);
		vPrintStringAndNumber(",", outputSample);

		vTaskDelayUntil(&xLastWakeTime, LOOP_SAMPLE_TIME);

		samplesCounter++;

	}

}
