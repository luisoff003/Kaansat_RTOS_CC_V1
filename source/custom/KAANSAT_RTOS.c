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

    if( xTaskCreate(vTask_DATA_RECOV, "RECOVERY", configMINIMAL_STACK_SIZE, NULL, DAT_REC_PRIOR, &xHandle_DATA_RECOV) != pdTRUE ){
        while(1);   /* Error */
    }

    return 0;
}

/*  Task 0:     WAIT TO START
 *  Wait until GCS signal is given to start mission. */
void vTask_WAIT2START(void *pcParameters){
//portTickType xLastWakeTimeWait;

    /* Start count on actual Tick */
//    xLastWakeTimeWait = xTaskGetTickCount();
    for(;;){

        /************************* QUitar ESTO JEJJEE */
        START_TELEMETRY = 1;     /**************** Cambiar por algoritmo para leer trama de GCS */

        /* Waiting here until GCS gives a signal to start */
        if( START_TELEMETRY ){
            /* Create tasks */
            if( xTaskCreate(vTask_TELEMETRY, "TELEMETRY", configMINIMAL_STACK_SIZE, NULL, TELEMETR_PRIOR, &xHandle_TELEMETRY) != pdTRUE ){
                while(1);   /* Error */
            }
            if( xTaskCreate(vTask_SENSORS, "SENSORS", configMINIMAL_STACK_SIZE, NULL, SENSOR_PRIOR, &xHandle_SENSORS) != pdTRUE ){
                while(1);   /* Error */
            }
            if( xTaskCreate(vTask_SAT_OPS, "MISSION OPS", configMINIMAL_STACK_SIZE, NULL, MISSION_PRIOR, &xHandle_SAT_OPS) != pdTRUE ){
                while(1);   /* Error */
            }

            /* Update Mission State */
            FSW_STATE = Telemetry_started;

            /* Delete WAIT2START task */
            vTaskDelete( xHandle_WAIT2START );
        }
        else{}

    }
}

/* Task 1:     DATA RECOVERY
 * Recover actual state of the mission from SD card. */
void vTask_DATA_RECOV(void *pcParameters){
portTickType xLastWakeTime;

    /* Start count on actual Tick */
    xLastWakeTime = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){
        /* Read states from SD card */
        FSW_STATE = Cansat_Ready;           /*<-----------------  Change for SD card reading STATE */

        /* Identify which state it is and set variables */
        switch( FSW_STATE ){
            case Cansat_Ready:
                /* Cansat is turned on */
                CansatReady_CreateState();
                break;

            case Telemetry_started:
                TelemetryStarted_CreateState();
                break;

            case Rocket_TakeOff:
                /* Means is getting higher
                 * Dh > 0 */
                RocketTakeOff_CreateState();
                break;

            case Rocket_Apogee:
                /* Max altitude */
                break;

            case Cansat_Separation:
                /* Cansat is outside the rocket */
                CansatSeparation_CreateState();
                break;

            case Payload_Realese:
                /* Payload starts gliding */
                PayloadRealese_CreateState();
                break;

            case Landing:
                /* Beacon */
                Landing_CreateState();
                break;
            default:
                /* Find a state to set to put in here
                 * without risking the mission. */
                break;
        }

        vTaskDelete( xHandle_DATA_RECOV );

    }
}

/* Task 2:     SENSORS
 * Update sensor data ( SPI/ADC/UART ) every 0.01s */
void vTask_SENSORS(void *pcParameters){
portTickType xLastWakeTimeSensors;

    /* Start count on actual Tick */
    xLastWakeTimeSensors = xTaskGetTickCount();

    /* Set pwm for Dust Sensor */
    pwm0_het0_DUST.duty = 320;
    pwm0_het0_DUST.period = 10000;
    pwmSetSignal10e3(hetRAM1, pwm0, pwm0_het0_DUST);
    pwmEnableNotification(hetREG1, pwm0, pwmEND_OF_DUTY);

    /* Infinite Loop */
    for(;;){
        /* ---------------- SPI ------------------- */
        /* Read Pressure/Temperature BMP280 */

        /* Altitude Derivative Dh */

        /* --------------- ADC ------------------- */
        if( Read_All_ADC(adcREG1, adcGROUP1, &ADC_0_7) == 0){
            VOLT_BATT = (float)Get_ADC_Value(AD_VOLT_BAT)*(3.3f/4096.0f);   /*< Read Battery Voltage    [V] */
            AIRSPEED = (float)Get_ADC_Value(AD_PITOT);                      /*< Read Airspeed           [m/s] */
            /* DUST is read by HET interrupt */
        }
        /* ---------------- SPI ------------------- */
        /* Read Mag/Accel/Gyro  MPU9250 */

        /* Euler Angles Calculation */

        /* Euler Angle Velocities */


        /* Sensors every 100ms */
        vTaskDelayUntil( &xLastWakeTimeSensors, T_SENSORS/ portTICK_RATE_MS  );
    }
}

/*  Task 3:     TELEMETRY
 *  Update time and send Telemetry  every 1s */
void vTask_TELEMETRY(void *pcParameters){
portTickType xLastWakeTimeTel;

    /* Start count on actual Tick */
    xLastWakeTimeTel = xTaskGetTickCount();

    /* Infinite Loop */
    for(;;){

        /* Update time */
        MISSION_TIME += (float)T;

        /* String creation */
        Create_Packets();

        /* Send string SCI */
        sciEnviarDatos(buff_size, command, 0);

        /* Update packet count */
        PACKET_COUNT++;

        vTaskDelayUntil( &xLastWakeTimeTel, T_TELEMETRY / portTICK_RATE_MS );
    }

}

/* Task 4:     SAT-OPS
 * Handles deployment conditions and save data into SD every 0.01s */
void vTask_SAT_OPS(void *pcParameters){
portTickType xLastWakeTimeSatOps;

    /* Start count on actual Tick */
    xLastWakeTimeSatOps = xTaskGetTickCount();
    for(;;){
        /* Rocket Take-Off Condition */
        if( 0 ){
            /* Change to Rocket_TakeOff State */
            FSW_STATE = Rocket_TakeOff;
        }
        else {}

        /* Release Payload Condition State */
        if( 0 ){
            /* Change to Cansat_Separation State */
            FSW_STATE = Cansat_Separation;
        }
        else {}

        /* Payload Release Condition */
        if( 0 ){
            FSW_STATE = Payload_Realese;
        }
        else {}

        /* Landing Condition */
        if( 0 ){
            FSW_STATE = Landing;
            Landing_CreateState();
        }
        else {}

        vTaskDelayUntil( &xLastWakeTimeSatOps, T_CONTROL / portTICK_RATE_MS );
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
        /* Control every 100ms */
        vTaskDelayUntil( &xLastWakeTime, T_CONTROL/ portTICK_RATE_MS  );
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
        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     1 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      2 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     3 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      4 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     5 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      6 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_SHORT_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     7 */
        /* Se duerme 1000 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      8 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     9 */
        /* Se duerme 1000 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      10 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 1);      /*< OFF     11 */
        /* Se duerme 1000 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);

        gioSetBit(PORT_BUZZER, GIO_BUZZER, 0);      /*< ON      12 */
        /* Se duerme 400 ms */
        vTaskDelayUntil(&xLastWakeTime, T_LONG_BUZZER/portTICK_RATE_MS);
    }
}

uint8_t CansatReady_CreateState(void){
    if( xTaskCreate(vTask_WAIT2START, "WAIT2START", configMINIMAL_STACK_SIZE, NULL, WAIT2START_PRIOR, &xHandle_WAIT2START) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}

uint8_t TelemetryStarted_CreateState(void){
    /* Telemetry */
    if( xTaskCreate(vTask_TELEMETRY, "TELEMETRY", configMINIMAL_STACK_SIZE, NULL, TELEMETR_PRIOR, &xHandle_TELEMETRY) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Sensors */
    if( xTaskCreate(vTask_SENSORS, "SENSORS", configMINIMAL_STACK_SIZE, NULL, SENSOR_PRIOR, &xHandle_SENSORS) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Mission Operations */
    if( xTaskCreate(vTask_SAT_OPS, "MISSION OPS", configMINIMAL_STACK_SIZE, NULL, MISSION_PRIOR, &xHandle_SAT_OPS) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}
uint8_t RocketTakeOff_CreateState(void){
    /* Telemetry */
    if( xTaskCreate(vTask_TELEMETRY, "TELEMETRY", configMINIMAL_STACK_SIZE, NULL, TELEMETR_PRIOR, &xHandle_TELEMETRY) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Sensors */
    if( xTaskCreate(vTask_SENSORS, "SENSORS", configMINIMAL_STACK_SIZE, NULL, SENSOR_PRIOR, &xHandle_SENSORS) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Mission Operations */
    if( xTaskCreate(vTask_SAT_OPS, "MISSION OPS", configMINIMAL_STACK_SIZE, NULL, MISSION_PRIOR, &xHandle_SAT_OPS) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}

uint8_t CansatSeparation_CreateState(void){
    /* Telemetry */
    if( xTaskCreate(vTask_TELEMETRY, "TELEMETRY", configMINIMAL_STACK_SIZE, NULL, TELEMETR_PRIOR, &xHandle_TELEMETRY) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Sensors */
    if( xTaskCreate(vTask_SENSORS, "SENSORS", configMINIMAL_STACK_SIZE, NULL, SENSOR_PRIOR, &xHandle_SENSORS) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Mission Operations */
    if( xTaskCreate(vTask_SAT_OPS, "MISSION OPS", configMINIMAL_STACK_SIZE, NULL, MISSION_PRIOR, &xHandle_SAT_OPS) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}

uint8_t PayloadRealese_CreateState(void){
    /* Telemetry */
    if( xTaskCreate(vTask_TELEMETRY, "TELEMETRY", configMINIMAL_STACK_SIZE, NULL, TELEMETR_PRIOR, &xHandle_TELEMETRY) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Sensors */
    if( xTaskCreate(vTask_SENSORS, "SENSORS", configMINIMAL_STACK_SIZE, NULL, SENSOR_PRIOR, &xHandle_SENSORS) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Mission Operations */
    if( xTaskCreate(vTask_SAT_OPS, "MISSION OPS", configMINIMAL_STACK_SIZE, NULL, MISSION_PRIOR, &xHandle_SAT_OPS) != pdTRUE ){
        while(1);   /* Error */
    }
    /* Autopilot/Camera Control */
    if( xTaskCreate(vTask_CONTROL, "CONTROL", configMINIMAL_STACK_SIZE, NULL, AUTOPILOT_PRIOR, &xHandle_CONTROL) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}

uint8_t Landing_CreateState(void){
    /* Delete other tasks */
    vTaskDelete( xHandle_SENSORS );
    vTaskDelete( xHandle_CONTROL );
    vTaskDelete( xHandle_TELEMETRY );

    /* Turn off all sensors */

    /* Buzzer */
    if( xTaskCreate(vTask_BUZZER, "BUZZER", configMINIMAL_STACK_SIZE, NULL, BUZZER_PRIOR, &xHandle_BUZZER) != pdTRUE ){
        while(1);   /* Error */
    }
    return 0;
}

/*< Inactivity task service */
void vApplicationIdleHook(void){
    /* Nothing to see here */
}
