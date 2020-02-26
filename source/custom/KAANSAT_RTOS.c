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
 * KAANSAT_RTOS.c
 *
 *  Created on: 27/08/2019
 *      Author: Luison
 */

#include "Custom/KAANSAT_RTOS.h"
#include "custom/Utilities.h"

/** @fn uint8_t CreateUserTasks(void)
*   @brief Creates tasks in order to be executed.
*   @param[out] uint8_t:  Task creation is OK.
*/
uint8_t CreateUserTasks(void){

    if( xTaskCreate(vTask_WAIT2START, "WAIT2START", configMINIMAL_STACK_SIZE, NULL, WAIT2START_PRIOR, &xHandle_WAIT2START) != pdTRUE ){
        while(1);   /* Error */
    }

    return 0;
}

/*  Task 0:     TIMER
 *  Wait until GCS signal is given to start mission. */
void vTask_WAIT2START(void *pcParameters){

    for(;;){

    }
}

/*  Task 1:     TELEMETRY
 *  Update time and send Telemetry  every 1s */
void vTask_TELEMETRY(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

        /* Update time */
        MISSION_TIME += (float)T;

        /* String creation */
        Create_Packets();

        /* Send string */
//        sciEnviarDatos(buff_size, command, 0);

        /* Update packet count */
        PACKET_COUNT++;

        vTaskDelayUntil( &xLastWakeTime, 1000 / portTICK_RATE_MS );

    }

}

/* Task 2:     SENSORS
 * Update sensor data ( SPI/ADC/UART ) every 0.01s */
void vTask_SENSORS(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

    }
}

/* Task 3:     SAT-OPS
 * Handles deployment conditions and save data into SD every 0.01s */
void vTask_SAT_OPS(void *pcParameters){

}

/* Task 4:     DATA RECOVERY
 * Recover actual state of the mission from SD card. */
void vTask_DATA_RECOV(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

    }
}

/* Task 5:     AUTOPILOT/CONTROL CAMERA
 * Circular controlled descend and camera gimbal control. */
void vTask_CONTROL(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

    }
}

/* Task 6:     BUZZER
 * Eneables buzzer sound in SOS pattern. */
void vTask_BUZZER(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

    }
}

/*< Inactivity task service */
void vApplicationIdleHook(void){
    /* Nothing to see here */
}
