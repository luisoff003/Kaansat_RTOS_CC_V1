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
 * PWM_Sensors.c
 *
 *  Created on: 27/02/2020
 *      Author: Luison
 *
 */

#include "custom/PWM_Sensors.h"

/* HET signal initial values (duty/period) */
hetSIGNAL_t pwm0_het0_DUST = {0, 10000};
hetSIGNAL_t pwm1_het2_LIBER = {SERVO_ATACHED, 20000};
hetSIGNAL_t pwm2_het4_SERVO_L = {SERVO_INITIAL_L,20000};
hetSIGNAL_t pwm3_het6_SERVO_R = {SERVO_INITIAL_R,20000};

void   pwmEnableNotification(hetBASE_t * hetREG,uint32 pwm, uint32 notification);
