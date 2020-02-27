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
 * PWM_Sensors.h
 *
 *  Created on: 27/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_PWM_SENSORS_H_
#define INCLUDE_CUSTOM_PWM_SENSORS_H_

/* Peripheral Libraries  */
#include "het.h"

/* Other libraries */
#include "Utilities.h"
#include "Servomotor.h"

/* HET signal initial values (duty/period) */
extern hetSIGNAL_t pwm0_het0_DUST;
extern hetSIGNAL_t pwm1_het2_LIBER;
extern hetSIGNAL_t pwm2_het4_SERVO_L;
extern hetSIGNAL_t pwm3_het6_SERVO_R;

/* pwmEnableNotification(hetREG1, pwm0, pwmEND_OF_DUTY); */
void   pwmEnableNotification(hetBASE_t * hetREG,uint32 pwm, uint32 notification);

#endif /* INCLUDE_CUSTOM_PWM_SENSORS_H_ */
