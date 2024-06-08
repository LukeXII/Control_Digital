/*
 * TaskPolePlacement.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskPolePlacement.h"

void TaskPolePlacement(void * argument)
{
	uint32_t xLastWakeTime, x1_sample, x2_sample, controlSignal_DAC;
	uint16_t setpoint = SQUARE_VALUE_1V;
	float controlSignal;

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SQUARE_VALUE_0V);
	vTaskDelay(1000);

	vPrintString("start--------");
	vPrintNewLine();

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{

		// Toma la muestra de la salida (X2)
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		x1_sample = HAL_ADC_GetValue(&hadc1);

		// Toma la muestra de X1
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		x2_sample = HAL_ADC_GetValue(&hadc1);

		// computa el valor de la ley de control
		controlSignal = Kf - K1*((float)(x1_sample)*ADC_RESOLUTION) - K2*((float)(x2_sample)*ADC_RESOLUTION);

		controlSignal_DAC = (uint32_t)((float)controlSignal/ADC_RESOLUTION);

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, controlSignal_DAC);

		vPrintNumber(setpoint);
		vPrintStringAndNumber(",", x1_sample);
		//vPrintStringAndNumber(",", x2_sample);
		//vPrintStringAndNumber(",", controlSignal_DAC);
		vPrintNewLine();

		vTaskDelayUntil(&xLastWakeTime, LOOP_SAMPLING_TIME);

	}

}
