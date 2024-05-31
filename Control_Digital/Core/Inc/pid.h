/*
 * pid.h
 *
 *  Created on: May 31, 2024
 *      Author: Lucas
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "math.h"
#include "usart.h"

typedef struct {
	/* Mode */
	unsigned short bypassPid; /* Disable pid entirely.*/

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;

	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Deadzone */
	float deadZone;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

float PIDController_Update(PIDController * pid, float setpoint, float measurement);

#endif /* INC_PID_H_ */
