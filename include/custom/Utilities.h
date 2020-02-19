/*
 * Utilities.h
 *
 *  Created on: 18/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_UTILITIES_H_
#define INCLUDE_CUSTOM_UTILITIES_H_

/* Standard Libraries */
#include "stdint.h"
#include "stdlib.h"

#include "custom/GPS.h"
#include "gio.h"
#include "het.h"

/* RTOS Libraries */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

/* ADC pin declarations */
#define AD_VOLT_BAT     0           /*< ADIN0 TMS570LS04 */
#define AD_PITOT        1           /*< ADIN1 TMS570LS04 */


#endif /* INCLUDE_CUSTOM_UTILITIES_H_ */
