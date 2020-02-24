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
 * Utilidades.c
 *
 *  Created on: 27/08/2019
 *      Author: Luison
 */


#include "Custom/Utilities.h"

/* -------------------------------------------------------------------
 *  GLOBAL VARIABLES
 * ------------------------------------------------------------------- */
char command[COMM_SIZE] = {};   /*< Allocates telemetry format to send. */
uint8_t buff_size = 0;   /*< Size of the telemetry string */

/* Mission time [s] */
float MISSION_TIME = 0.0;
char cMISSION_TIME[6];

/* Packet Count [Units] */
int PACKET_COUNT = 0;
char cPACKET_COUNT[6] = "XXXXXX";

/* Altitude [m] */
float ALTITUDE_BAR = 0.0;
char cALTITUDE_BAR[8] = "XXXXXXXX";

/* Pressure [Pa] */
float PRESS_BAR = 0.0;
char cPRESS_BAR[8] = "XXXXXXXX";


/* Temperature [°C] */
float TEMPERATURE = 0.0;
char cTEMPERATURE[8] = "XXXXXXXX";

/* Battery Voltage [v] */
float VOLT_BATT = 0.0;
char cVOLT_BATT[4] = "XXXX";

/* GPS Lat/Lon [Decimal Deg] */
char cLAT[10] ;           /* Latitude */
char cLON[10] ;           /* Longitude */

/* GPS Altitude [m] */
char cALT[7] ;            /* Altitude */
char cNSATS[3] ;

/* Airspeed [m/s] */
float AIRSPEED;
char cAIRSPEED[5];

/* Software State [int] */
uint8_t FSW_STATE;
char cFSW_STATE[4];

/* Particle Count [mg/m^3] */
float PARTICLES;
char cPARTICLES[6];

/* BONUS Magnetic North */
float MAG_NORTH;
char cMAG_NORTH[6];

/* SPI DATA OK? */
int dataSPI_ok = 0;     /*<This variable avoids RTOS crashes */
/* -------------------------------------------------------------------
 *  FUNCTIONS
 * ------------------------------------------------------------------- */
/* Prepara los paquetes de datos a mandar.
 * Nota: En RTOS no funciona sprintf con variables tipo float.
 *       Se debe usar sprintf("%s", CADENA); */
void Create_Packets(void){
    /* Float to String CONVERSION
     *  NOTE: RTOS crashes with %f into sprintf as follow:
     *      sprintf( buf, "%f", (float)100.0 );
     *
     *  Convert float data into strings to send.
     */

    /* MISSION TIMER:       2 */
    ftoa(MISSION_TIME, cMISSION_TIME, 0);

    /* PACKET COUNT:        3*/
    ftoa(PACKET_COUNT, cPACKET_COUNT, 0);

    if( dataSPI_ok == 1 ){
        /* ALTITUDE:        4 */
        ftoa(ALTITUDE_BAR, cALTITUDE_BAR, 1);

        /* PRESSURE:        5 */
        ftoa((float)PRESS_BAR, cPRESS_BAR, 0);

        /* TEMPERATURE :    6 */
        ftoa(TEMPERATURE, cTEMPERATURE, 1);
    }

    /* VOLT DE LA BATERIA:  7 */
    ftoa(VOLT_BATT, cVOLT_BATT, 2);

    /* GPS LATITUDE:        9 */
    ftoa(xGPSdata.Lat, cLAT, 5);

    /* GPS LONGITUDE:       10 */
    ftoa(xGPSdata.Long, cLON, 5);

    /* GPS ALTITUDE:        11 */
    ftoa(xGPSdata.Alt, cALT, 1);

    /* GPS SATS:            12 */
    ftoa(xGPSdata.nSats, cNSATS, 0);

    /* AIRSPEED:            13 */
    ftoa(AIRSPEED, cAIRSPEED, 1);

    /* SOFTWARE STATE:      14 */
    ftoa(FSW_STATE, cFSW_STATE, 0);

    /* PARTICLE COUNT:      15 */
    ftoa(PARTICLES, cPARTICLES, 2);

    /* BONUS DATA:          16 */
    ftoa(MAG_NORTH, cMAG_NORTH, 1);

    /* Create Telemetry string
     * NOTE: Only char variables are allowed at this section. */
    buff_size = sprintf (command,
                       "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s;\r\n\0",
                     /* 01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16; */
                           "5120",              /* Team ID:         1 */
                           cMISSION_TIME,       /* Mission time:    2 */
                           cPACKET_COUNT,       /* Packet Count:    3 */
                           cALTITUDE_BAR,       /* Altitude Bar:    4 */
                           cPRESS_BAR,          /* Pressure Bar:    5 */
                           cTEMPERATURE,        /* Temperature:     6 */
                           cVOLT_BATT,          /* Batt Volt:       7 */
                           xGPSdata.utcTime,    /* GPS Time:        8 */
                           cLON,                /* GPS Longitude:   9 */
                           cLAT,                /* GPS Latitude:    10 */
                           cALT,                /* GPS Altitude:    11 */
                           cNSATS,              /* No. SatGPS:      12 */
                           cAIRSPEED,           /* Airspeed:        13 */
                           cFSW_STATE,          /* Software State:  14 */
                           cPARTICLES,          /* Particle Count:  15 */
                           cMAG_NORTH           /* Bonus Data:      16 */
                           );

}


/** @fn void ftoa(float n, char *res, int afterpoint)
*   @brief Convierte una variable tipo float en una cadena de char[]
*   @param[in] n:           Variable tipo float a convertir.
*   @param[in] res: char    Cadena de char.
*   @param[in] afterpoint:  El numero de decimales deseados en la conversion.
*/
void ftoa(float n, char *res, int afterpoint){
    int ipart = (int)n, fpart = 0;
    /* Convertir parte entera */
    int i = sltoa(res, ipart );
    /* Agregar parte decimal */
    if(afterpoint > 0){
        res[i] = '.';
        fpart = (int)(( n - (float)ipart ) * pow(10, afterpoint ));
        sltoa(&res[i+1], abs(fpart) );
    }

}

/** @fn size_t sltoa(char *s, long int n)
*   @brief Convierte una variable tipo float en una cadena de char[]
*   @param[in] n:    pointer tipo xGPsdata en donde guardar datos
*   @param[in] : char actual recibido por el GPS.
*   @param[in] : char actual recibido por el GPS.
*/
size_t sltoa(char *s, long int n) {
    size_t i = 0;
    long int sign_mask;
    unsigned long int nn;

    sign_mask = n >> sizeof(long int) * 8 - 1;
    nn = (n + sign_mask) ^ sign_mask;
    do {
        s[i++] = nn % 10 + '0';
    } while (nn /= 10);

    s[i] = '-';
    i += sign_mask & 1;
    s[i] = '\0';

    reverse(s, i);
    return (i);
}

static void reverse(char *s, size_t s_len) {
    size_t i, j;
    char swap;

    for (i = 0, j = s_len - 1; i < j; ++i, --j) {
        swap = s[i];
        s[i] = s[j];
        s[j] = swap;
    }
}
