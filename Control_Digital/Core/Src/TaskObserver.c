/*
 * TaskObserver.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskObserver.h"

void TaskObserver(void * argument)
{
	uint32_t xLastWakeTime, x2_sample, controlSignal_DAC;
	uint16_t setpoint = SQUARE_VALUE_1V;
	float controlSignal, x1_hat, x1_hat_next = 0.0, x2_hat, x2_hat_next = 0.0, res = 3.3/4095.0;

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, SQUARE_VALUE_0V);
	vTaskDelay(1000);

	vPrintString("start--------");
	vPrintNewLine();
	vPrintNumber(setpoint);
	vPrintStringAndNumber(",", 0);
	vPrintNewLine();

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		// Toma la muestra de la salida (X2)
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
		x2_sample = HAL_ADC_GetValue(&hadc1);

		x1_hat = x1_hat_next;
		x2_hat = x2_hat_next;

		// computa el valor de la ley de control
		controlSignal = Kf - K1*x1_hat - K2*x2_hat;

		// estimacion de estados
		x1_hat_next = A11*x1_hat + A12*x2_hat + B1*controlSignal + L1*((float)(x2_sample)*ADC_RESOLUTION - C1*x1_hat);
		x2_hat_next = A21*x1_hat + A22*x2_hat + B2*controlSignal + L2*((float)(x2_sample)*ADC_RESOLUTION - C2*x2_hat);

		controlSignal_DAC = (uint32_t)(controlSignal/res);

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, controlSignal_DAC);

		vPrintNumber(setpoint);
		vPrintStringAndNumber(",", x2_sample);
		//vPrintStringAndNumber(",", x1_hat);
		//vPrintStringAndNumber(",", controlSignal_DAC);
		vPrintNewLine();

		vTaskDelayUntil(&xLastWakeTime, LOOP_SAMPLING_TIME);

	}

}
