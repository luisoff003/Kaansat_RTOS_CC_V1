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
 * KAANSAT_RTOS.h
 *
 *  Created on: 25/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_KAAN_RTOS_H_
#define INCLUDE_CUSTOM_KAAN_RTOS_H_

#include <sys/stdint.h>

/* RTOS Libraries */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

/* Other Libraries */
#include "custom/Utilities.h"   /* Library with important declarations */
#include "Custom/Servomotor.h"  /* Servomotor Library */
#include "custom/GPS.h"         /* GPS Library */

/* Task Priorities */
#define     WAIT2START_PRIOR    3       /*  1  */
#define     DAT_REC_PRIOR       4       /*  2  */
#define     SENSOR_PRIOR        1       /*  3  */
#define     TELEMETR_PRIOR      2       /*  4  */
#define     AUTOPILOT_PRIOR     1       /*  5  */
#define     MISSION_PRIOR       1       /*  6  */
#define     BUZZER_PRIOR        3       /*  7  */

/* Sample/Task Periods */
#define     T_TELEMETRY        1000     /*< Telemetry Task Period [ms] Best fit 100/ 100Hz tick */
#define     T_SENSORS           10     /*< Sensors Task Period */
#define     T_CONTROL           20     /*< Control/Autopilot Period */
#define     T    T_TELEMETRY/1000.0     /*< Telemetry Task Period [s] */
#define     T_SHORT_BUZZER      400     /*< Short period for BUZZER [ms] */
#define     T_LONG_BUZZER      1000     /*< Long period for BUZZER [ms] */
/*--------------------------------
 *          RTOS Tasks
 *--------------------------------*/
void vApplicationIdleHook(void);        /*< Inactivity task service */

/*  Task 0:     TIMER
 *  Wait until GCS signal is given to start mission. */
void vTask_WAIT2START(void *pcParameters);
xTaskHandle xHandle_WAIT2START;         /*< Handle variable for WAIT2START task */

/*  Task 1:     TELEMETRY
 *  Update time and send Telemetry  every 1s */
void vTask_TELEMETRY(void *pcParameters);
xTaskHandle xHandle_TELEMETRY;              /*< Handle variable for TIMER task */

/* Task 2:     SENSORS
 * Update sensor data ( SPI/ADC/UART ) every 0.01s */
void vTask_SENSORS(void *pcParameters);
xTaskHandle xHandle_SENSORS;         /*< Handle variable for SENSORS task */

/* Task 3:     SAT-OPS
 * Handles deployment conditions and save data into SD every 0.01s */
void vTask_SAT_OPS(void *pcParameters);
xTaskHandle xHandle_SAT_OPS;         /*< Handle variable for SAT_OPS task */

/* Task 4:     DATA RECOVERY
 * Recover actual state of the mission from SD card. */
void vTask_DATA_RECOV(void *pcParameters);
 xTaskHandle xHandle_DATA_RECOV;      /*< Handle variable for DATA_RECOV task */

/* Task 5:     AUTOPILOT/CONTROL CAMERA
 * Circular controlled descend and camera gimbal control. */
void vTask_CONTROL(void *pcParameters);
xTaskHandle xHandle_CONTROL;         /*< Handle variable for DATA_RECOV task */

/* Task 6:     BUZZER
 * Eneables buzzer sound in SOS pattern. */
void vTask_BUZZER(void *pcParameters);
xTaskHandle xHandle_BUZZER;          /*< Handle variable for DATA_RECOV task */

uint8_t CreateUserTasks(void);      /*< User Tasks */

uint8_t CansatReady_CreateState(void);
uint8_t TelemetryStarted_CreateState(void);
uint8_t RocketTakeOff_CreateState(void);
uint8_t CansatSeparation_CreateState(void);
uint8_t PayloadRealese_CreateState(void);
uint8_t Landing_CreateState(void);

#endif /* INCLUDE_CUSTOM_KAAN_RTOS_H_ */
