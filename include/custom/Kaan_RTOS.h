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
 * Kaan_RTOS.h
 *
 *  Created on: 18/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_KAAN_RTOS_H_
#define INCLUDE_CUSTOM_KAAN_RTOS_H_

/* RTOS Libraries */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

/* Task Priorities */
#define     WAIT_GCS_PRIOR      4       /*  1  */
#define     DAT_REC_PRIOR       3       /*  2  */
#define     SENSOR_PRIOR        1       /*  3  */
#define     TELEMETR_PRIOR      3       /*  4  */
#define     AUTOPILO_PRIOR      4       /*  5  */
#define     MISSION_PRIOR       3       /*  6  */
#define     BUZZER_PRIOR        3       /*  7  */




#endif /* INCLUDE_CUSTOM_KAAN_RTOS_H_ */
