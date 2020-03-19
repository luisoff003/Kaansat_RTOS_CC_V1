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

#define L0_def      -0.0065         /* [K/m] Rate of temperature decrease in lower atmosphere*/
#define T0_def      288.15          /* [K] Standard temperature at sea level */
#define M_def       0.0289644       /* [kg/mol] Standard molar mass of atmospheric air */
#define R_def       8.31432         /*[Nm/(mol-k)] Universal gas constant for air */
#define P0_def      101325          /* [N/m^2] Standard pressure at sea level*/

#define MAX_PRES    101.325     /* [kPa] Maximum pressure of sensor */
#define const_rho   1.22        /* [kg/m^3] Air density */

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

float Get_Airspeed(int ADC);

#endif /* INCLUDE_CUSTOM_ADC_SENSORS_H_ */
