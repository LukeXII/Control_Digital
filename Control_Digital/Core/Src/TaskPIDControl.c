/*
 * TaskPIDControl.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskPIDControl.h"
#include "pid.h"

static PIDController pid = {
    .bypassPid = 0,

    // Control parameters
    .Kp = 1.0,
    .Ki = 32.0,
    .Kd = 0.005,
    .tau = 1.0 * LOOP_SAMPLING_TIME/1000,
    .limMin = -5,
    .limMax = 5,
    .limMinInt = -10.0,
    .limMaxInt = 10.0,
    .deadZone = 0.000,
    .T = 1.0 * LOOP_SAMPLING_TIME/1000,

    // Internal variables
    .integrator = 0.0f,
    .prevError = 0.0f,
    .differentiator = 0.0f,
    .prevMeasurement = 0.0f,
    .out = 0.0f,
};

void TaskPIDControl(void * argument)
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
		outputSample = HAL_ADC_GetValue(&hadc1);

		controlSignal = PIDController_Update(&pid, (float)setpoint*res, (float)outputSample*res);

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, (uint32_t)((float)controlSignal/res) );

		vPrintNumber(setpoint);
		vPrintStringAndNumber(",", outputSample);
		vPrintStringAndNumber(",", (uint32_t)((float)controlSignal/res));
		vPrintNewLine();

		vTaskDelayUntil(&xLastWakeTime, LOOP_SAMPLING_TIME);

	}

}
