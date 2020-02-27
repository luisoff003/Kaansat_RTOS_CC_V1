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
 * ADC_Sensors.c
 *
 *  Created on: 26/02/2020
 *      Author: Luison
 */

#include "custom/ADC_Sensors.h"

ADC_channel ADC_0_7;

static adcData_t ADC_RAW[6];
static int ch_count=0;
static int i_j=0;


/** @fn int Read_All_ADC(adcBASE_t *adc,uint32 group, ADC_channel *ADC_data)
*   @brief Returns ADC conversions
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[in] ADC_data Where data will be storage.
*
*   This function saves all data into ADC_channel type variable.
*
*/
uint8_t Read_All_ADC(adcBASE_t *adc,uint32 group, ADC_channel *ADC_data){
    adcStartConversion(adc, group);
    while ( adcIsConversionComplete(adc, group) == 0);
    ch_count = adcGetData(adc, group, &ADC_RAW[0]);
    i_j = 0;
    while( ch_count > 0 ){
      ADC_0_7.id[i_j] = ADC_RAW[i_j].id;
      ADC_0_7.ADC_conv[i_j] = ADC_RAW[i_j].value;
      ch_count--;
      i_j++;
    }
    return 0;
}

int Get_ADC_Value(int ID){
    return ADC_0_7.ADC_conv[ID];
}
