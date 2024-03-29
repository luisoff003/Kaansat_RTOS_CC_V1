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
 * Servomotor.c
 *
 *  Created on: 23/09/2019
 *      Author: Luison
 */

#ifndef SOURCE_CUSTOM_SERVOMOTOR_C_
#define SOURCE_CUSTOM_SERVOMOTOR_C_

#include "custom/Servomotor.h"

void pwmSetSignal10e3(hetRAMBASE_t * hetRAM, uint32 pwm, hetSIGNAL_t signal){
        uint32 action;
        uint32 pwmPolarity = 0U;
        float64 pwmPeriod = 0.0F;

        if(hetRAM == hetRAM1)
        {
            pwmPeriod = (signal.period * 1000.0F) / 800.000F;
            pwmPolarity = s_het1pwmPolarity[pwm];
        }
        else
        {
        }
        if (signal.duty == 0U)
        {
            action = (pwmPolarity == 3U) ? 0U : 2U;
        }
        else if (signal.duty >= 10000U)
        {
            action = (pwmPolarity == 3U) ? 2U : 0U;
        }
        else
        {
            action = pwmPolarity;
        }

        hetRAM->Instruction[(pwm << 1U) + 41U].Control = ((hetRAM->Instruction[(pwm << 1U) + 41U].Control) & (~(uint32)(0x00000018U))) | (action << 3U);
        hetRAM->Instruction[(pwm << 1U) + 41U].Data = ((((uint32)pwmPeriod * signal.duty) / 10000U) << 7U ) + 128U;
        hetRAM->Instruction[(pwm << 1U) + 42U].Data = ((uint32)pwmPeriod << 7U) - 128U;

    }

#endif /* SOURCE_CUSTOM_SERVOMOTOR_C_ */
