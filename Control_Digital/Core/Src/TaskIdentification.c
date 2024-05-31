/*
 * TaskIdentification.c
 *
 *  Created on: May 27, 2024
 *      Author: Lucas
 */

#include "TaskIdentification.h"

void TaskIdentification(void * argument)
{
	uint32_t xLastWakeTime;
	t_ILSdata * tILS = (t_ILSdata *) argument;

	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

#if (WAVEFORM_DEBUG == 1)
	vPrintString("start--------");
	vPrintNewLine();
#endif

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		ILS_Run(tILS);

        if(tILS->i==2)
        {
		#if (WAVEFORM_DEBUG == 0)
			// Imprimo los parámetros calculados
			console_print(tILS->buffer_T);
		#endif
        }

		vTaskDelayUntil( &xLastWakeTime, ( tILS->ts_Ms / portTICK_RATE_MS ) );

	}

}

// Generación del DAC y captura del ADC
void receiveData (float * buffer)
{
    float Y, U;
    uint16_t dacValue = 0, outputSample;

    // random = limite_inferior + rand() % (limite_superior +1 - limite_inferior);
    dacValue = DAC_REFERENCE_VALUE_LOW + rand() % (DAC_REFERENCE_VALUE_HIGH +1 - DAC_REFERENCE_VALUE_LOW);

	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dacValue);

	HAL_ADC_Start(&hadc1);

    U = (float) dacValue * 3.3 / 4095.0;

	outputSample = HAL_ADC_GetValue(&hadc1);

	Y = (float) outputSample * 3.3 / 4095.0;

#if (WAVEFORM_DEBUG == 1)
	vPrintNumber(dacValue);
	vPrintStringAndNumber(",", outputSample);
#endif

	buffer[0] = U;
	buffer[1] = Y;
}

// Función para imprimir los parámetros la planta (2do orden)
void console_print (float* buffer)
{
	uint32_t i;
	int32_t integer, fraction;

	// Imprimo los parámetros calculados
	printf ("Parametros = [\t");
	for (i = 0; i<5; i++)
	{
		// Casteo de float a int
		integer = (int)buffer[i];
		fraction = (int)(((buffer[i] - (float)integer)) * 1000);
        if (fraction<0)
        {
            fraction = (-1)*fraction;
            if (integer==0)
            {
            	taskENTER_CRITICAL();
            	{
            		printf("-%d.%03d\t", integer, fraction);
            		fflush( stdout );
            	}
            	taskEXIT_CRITICAL();
            }
            else
            {
            	taskENTER_CRITICAL();
            	{
            		printf("%d.%03d\t", integer, fraction);
            		fflush( stdout );
            	}
            	taskEXIT_CRITICAL();
            }
        }
        else
        {
        	taskENTER_CRITICAL();
        	{
            	printf("%d.%03d\t", integer, fraction);
        		fflush( stdout );
        	}
        	taskEXIT_CRITICAL();
        }
	}
	printf("]");
	vPrintNewLine();
}
