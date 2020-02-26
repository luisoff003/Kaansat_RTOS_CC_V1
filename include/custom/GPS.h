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
 * GPS.h
 *
 *  Created on: 26/08/2019
 *      Author: Luison
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */

#ifndef INCLUDE_CUSTOM_GPS_H_
#define INCLUDE_CUSTOM_GPS_H_

#include "stdio.h"
#include "math.h"
#include "stdint.h"

/* ------- GPS ------- */

/* GPGGA - Global Positioning Systema Data */
typedef struct{
    char utcTime[8];        /* hhmmss.ss */
    /* Latitud y Longitud
     * N, E: Positive  +
     * S, W: Negative  -
     */
        /* Latitud  [-90,90] */

    int dLat;           /* dd: degree */
    float mLat;         /* mm.mmmmm: minute */
    double Lat;         /* xxxx.xxxx: Decimal Degrees */

        /* Longitud [0,360] */

    int dLong;          /* ddd: degree */
    float mLong;        /* mm.mmmmm: minute */
    double Long;        /* xxxx.xxxx: Decimal Degrees */

    unsigned int nSats; /*  No satelites */

        /* Altitud GPS */
    float Alt;
}xGPGGA;

/* Position (x,y,z) */
typedef struct{
    double x;
    double y;
    double z;
}xPosition;

/*--------------------------------
 *    Variables globales GPS
 *--------------------------------*/
/* Variable datos de GPS actual */
extern xGPGGA xGPSdata;

/* Variable datos de GPS temporal */
extern xGPGGA xGPSn;


/*--------------------------------
 *         Funciones GPS
 *--------------------------------*/
/* Obtener datos de cadena GPS GPGGA completa */
uint8_t getData_GPS( xGPGGA *pGPSdata, unsigned char GPGGA_string );

/* ------- GPS ------- */

#endif /* INCLUDE_CUSTOM_GPS_H_ */
