/*
 * KAAN SAT TEAM PROPRIETARY INFORMATION - kaansat@soyunaq.mx
 *
 * Property of KA'AN SAT TEAM from Universidad Aeronautica en Queretaro,
 * Unauthorized reproduction and/or distribution in other universities
 * is strictly prohibited.
 *
 * Redistribution of code between KA'AN SAT TEAM members is permitted,
 * under the following conditions:
 *
 *  Redistribution of source code is under the KAANSAT TEAM name.
 *
 *  Any part of the software will not be used by other teams or
 *  organizations.
 *
 * -------------------------------------------------------------------
 *      FILE DESCRIPTION
 * -------------------------------------------------------------------
 *
 * Servomotor.h
 *
 *  Created on: 23/09/2019
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_SERVOMOTOR_H_
#define INCLUDE_CUSTOM_SERVOMOTOR_H_

#include "het.h"

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
