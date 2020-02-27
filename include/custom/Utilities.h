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

/* Other libraries */
#include "custom/GPS.h"
#include "custom/ADC_Sensors.h"

/* ADC pin declarations */
#define AD_VOLT_BAT         0           /*< ADIN0 TMS570LS04 */
#define AD_PITOT            1           /*< ADIN1 TMS570LS04 */
#define AD_DUST             2           /*< ADIN2 TMS570LS04 */

/* GIO pin declarations */
#define GIO_ON_OFFLED       0           /*< GIOA0 TMS570LS04 */
#define GIO_BUZZER          4           /*< GIOA1 TMS570LS04 */
#define PORT_BUZZER         hetPORT1    /*< Buzzer Port */

/* HET pin declarations */
#define HET_DUST            pwm0           /*< HET00 TMS570LS04 */
#define HET_SERVO_LIB       pwm1           /*< HET02 TMS570LS04 */
#define HET_SERVOCTRL_L     pwm2           /*< HET04 TMS570LS04 */
#define HET_SERVOCTRL_R     pwm3           /*< HET06 TMS570LS04 */

#define COMM_SIZE     255

/* Current states for the Mission */
enum Mission_States{
    Cansat_Ready        = 0U,
    Telemetry_started   = 1U,
    Rocket_TakeOff      = 2U,
    Rocket_Apogee       = 3U,
    Cansat_Separation   = 4U,
    Payload_Realese     = 5U,
    Landing             = 6U
};

/* -------------------------------------------------------------------
 *  GLOBAL VARIABLES
 * ------------------------------------------------------------------- */
extern char command[COMM_SIZE];   /*< Allocates telemetry format to send. */
extern uint8_t buff_size;   /*< Size of the telemetry string */

/* Mission time [s] */
extern float MISSION_TIME;
extern char cMISSION_TIME[6];

/* Packet Count [Units] */
extern int PACKET_COUNT;
extern char cPACKET_COUNT[6];

/* Altitude [m] */
extern float ALTITUDE_BAR;
extern char cALTITUDE_BAR[8];

/* Pressure [Pa] */
extern float PRESS_BAR;
extern char cPRESS_BAR[8];

/* Temperature [°C] */
extern float TEMPERATURE;
extern char cTEMPERATURE[8];

/* Battery Voltage [v] */
extern float VOLT_BATT;
extern char cVOLT_BATT[4];

/* GPS Lat/Lon [Decimal Deg] */
extern char cLAT[10] ;
extern char cLON[10] ;

/* GPS Altitude [m] */
extern char cALT[7] ;

/* GPS Satellites */
extern char cNSATS[3] ;

/* Airspeed [m/s] */
extern float AIRSPEED;
extern char cAIRSPEED[5];

/* Software State [int] */
extern uint8_t FSW_STATE;
extern char cFSW_STATE[4];

/* Particle Count [mg/m^3] */
extern float PARTICLES;
extern char cPARTICLES[6];

/* BONUS Magnetic North */
extern float MAG_NORTH;
extern char cMAG_NORTH[6];

/* SPI DATA OK? */
extern int dataSPI_ok;

/* GCS signal is given */
extern uint8_t START_TELEMETRY;

/* Historical Altitude */
extern int h_Altitude[10];

/* -------------------------------------------------------------------
 *  FUNCTIONS
 * ------------------------------------------------------------------- */

/* Prepara los paquetes de datos a mandar.
 * Nota: En RTOS no funciona sprintf con variables tipo float.
 *       Se debe usar sprintf("%s", CADENA); */
void Create_Packets(void);

/*  Convierte float a cadenas */
void ftoa(float n, char *res, int afterpoint);
static void reverse(char *, size_t);
size_t  sltoa(char *s, long int n);

/* Enviar datos por serial */
bool sciEnviarDatos(uint8 numOfDat, char* charDat, bool sc);

#endif /* INCLUDE_CUSTOM_UTILITIES_H_ */
