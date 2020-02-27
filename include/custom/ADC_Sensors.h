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
 * ADC_Sensors.h
 *
 *  Created on: 24/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_ADC_SENSORS_H_
#define INCLUDE_CUSTOM_ADC_SENSORS_H_

#include "Utilities.h"

typedef struct{
    int id[8];
    int ADC_conv[8];
}ADC_channel;

extern ADC_channel ADC_0_7;

static adcData_t ADC_RAW[6];
static int ch_count;
static int i_j;

uint8_t Read_All_ADC(adcBASE_t *adc,uint32 group, ADC_channel *ADC_data);
int Get_ADC_Value(int ID);

#endif /* INCLUDE_CUSTOM_ADC_SENSORS_H_ */
