/*
 * pid.c
 *
 *  Created on: May 31, 2024
 *      Author: Lucas
 */

#include "pid.h"

float PIDController_Update(PIDController * pid, float setpoint, float measurement)
{
    if (pid->bypassPid) {
        return setpoint;
    }

    // Error signal
    float error = setpoint - measurement;

    if (fabs(error) < pid->deadZone) {
        return pid->out;
    }

    // Proportional
    float proportional = pid->Kp * error;

    // Integral
    pid->integrator =
        pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

    /* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->limMaxInt) {
        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {
        pid->integrator = pid->limMinInt;
    }

    // Derivative (band-limited differentiator)

    pid->differentiator =
        -(2.0f * pid->Kd *
              (measurement -
               pid->prevMeasurement) /* Note: derivative on measurement,
                                        therefore minus sign in front of
                                        equation! */
          + (2.0f * pid->tau - pid->T) * pid->differentiator) /
        (2.0f * pid->tau + pid->T);

    // Compute output and apply limits
    pid->out = proportional + pid->integrator + pid->differentiator;

    if (pid->out > pid->limMax) {
        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {
        pid->out = pid->limMin;
    }

    /* Store error and measurement for later use */
    pid->prevError = error;
    pid->prevMeasurement = measurement;
    //vPrintStringAndNumber("prop", (uint32_t)proportional);
    /* Return controller output */
    return pid->out;
}
