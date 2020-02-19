/*
 * Servomotor.h
 *
 *  Created on: 23/09/2019
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_SERVOMOTOR_H_
#define INCLUDE_CUSTOM_SERVOMOTOR_H_

static const uint32 s_het1pwmPolarity[8U] =
{
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
    3U,
};

void pwmSetSignal10e3(hetRAMBASE_t * hetRAM, uint32 pwm, hetSIGNAL_t signal);


#endif /* INCLUDE_CUSTOM_SERVOMOTOR_H_ */
