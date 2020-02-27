/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
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
 */

/* Standard Libraries */
#include <math.h>

/* Peripheral Libraries  */
#include "sci.h"
#include "gio.h"
#include "adc.h"
#include "het.h"
#include "spi.h"

/* RTOS Libraries */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

/* Other Libraries */
#include "custom/Utilities.h"   /* Library with important declarations */
#include "Custom/Servomotor.h"  /* Servomotor Library */
#include "custom/GPS.h"         /* GPS Library */
#include "Custom/KAANSAT_RTOS.h"

//#include "Custom/LSM303D.h"     /* Libreria Acelerometro/Termometro/Magnetometro WONT USE :(*/

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

/* Preprocessor variables */

#define G_gravity   9.80665 /*[m/s^2]   Cte gravitacional */


/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

/*--------------------------------
 *          RTOS Tasks
 *--------------------------------*/
void vApplicationIdleHook(void);    /*< Funcion de servicio de Inactividad */

/* ------------------------------
 *              SCI
 * ------------------------------*/
/* SCI Interruption */
void sciNotification(sciBASE_t *sci, unsigned flags );
/* Received Variable */
static unsigned char receivedData[2];
static unsigned char receivedData_2[2];


/* ------------------------------
 *              HET
 * ------------------------------*/
/* HET interrupt */
void   pwmNotification(hetBASE_t * hetREG,uint32 pwm, uint32 notification);

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    /* Peripherals */
    sciInit();
    gioInit();
    spiInit();
    hetInit();
    adcInit();

    sciEnableNotification(scilinREG, SCI_RX_INT);

    _enable_IRQ();
    _enable_interrupt_();

    /* Await further character */
    sciReceive(scilinREG, 1, ( unsigned char *)receivedData);

    /* Check FSW State */
    /* --------Read SD card---------- */

    CreateUserTasks();

    vTaskStartScheduler();    /*< Start scheduler */

    while(1){
        /*< RTOS shall not get in this line */
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* SCI Interruption */
void sciNotification(sciBASE_t *sci, unsigned flags ){
        /* Echo received character
         * Debe estar comentado para no ver lo que recibe por SCI */
   // sciSend(sci, 1, (unsigned char *)&receivedData);

        /* Await further character */
    sciReceive(sci, 1, (unsigned char *)&receivedData);
    receivedData_2[0] = receivedData[0];

    /* Guardar datos de cadenas GPS completas */
    if( getData_GPS( &xGPSn, receivedData_2[0] ) ){
        /* Actualizar nuevas posiciones */
        xGPSdata = xGPSn;
    }

}

void   pwmNotification(hetBASE_t * hetREG,uint32 pwm, uint32 notification){
    /* Update Dust Sensor value */
    PARTICLES = (float)(11.0f/81900.0f) *
                ( Get_ADC_Value(AD_DUST) - (6825.0f/11.0f) );           /*< Read Dust Sensor        [mg/mm^3] */
}

/* USER CODE END */
