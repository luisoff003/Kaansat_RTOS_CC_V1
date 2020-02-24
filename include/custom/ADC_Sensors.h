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

/* ------------------------------
 *              ADC
 * ------------------------------*/
typedef struct{
    int id[8];
    int ADC_conv[8];
}ADC_channel;
ADC_channel ADC_0_7;
extern static adcData_t ADC_RAW[6];
extern static int ch_count=0;
extern static int i_j=0;



#endif /* INCLUDE_CUSTOM_ADC_SENSORS_H_ */
