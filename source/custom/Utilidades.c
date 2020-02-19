/*
 * Utilidades.c
 *
 *  Created on: 27/08/2019
 *      Author: Luison
 */
#include "Custom/Utilidades.h"
#include <stdlib.h>
#include "string.h"
#include <stdio.h>

/* Librerias RTOS */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"
#define SIZE_CADENA_CANSAT      255
/* --------------------------------
 *  VARIABLES IMPORTANTES GLOBALES
 * -------------------------------- */
/* Buffer guarda cadena a enviar */
char command[SIZE_CADENA_CANSAT] = {};

/* Tamano de buffer */
uint8_t buff_size = 0;

/* Tiempo de mision transcurrido s */
float fMISION_TIMER = 0.0;
char MISION_TIMER[6] = "XXXXXX";

/* Numero de paquetes enviados */
int dN_PAQ = 1;
char N_PAQ[6] = "XXXXXX";

/* Cadenas de GPS */
char cDegLAT[10] = "XXXXXXX";       /* Grados Latitud */
char cMinLAT[10] = "XXXXXXX";       /* Minutos Latitud */
char cDegLON[10] = "XXXXXXX";       /* Grados Longitud */
char cMinLON[10] = "XXXXXXX";       /* Minutos Longitud */
char cALT[7] = "XXXXXX";            /* Altitud */
char cNSATS[3] = "X";

/* Voltaje de la bateria */
float VOLT_BAT = 0.0;
char cVOLT_BAT[4] = "XXX";

/* Temperatura interna */
float TEMP_INTER = 0.0;
char cTEMP_INTER[8] = "XXXXXXX";

/* Magnetometro*/
float magnetometroxyz[3] = {};
char cMAGNETOX[8] = "XXXXXXX";
char cMAGNETOY[8] = "XXXXXXX";
char cMAGNETOZ[8] = "XXXXXXX";

/*  Acelerometro  */
int datos_ok=0,datos_ok2 = 0;
float acelerometroxyz[3] = {0.0,0.0,0.0};
char cACELEROX[8] = "XXXXXXX";
char cACELEROY[8] = "XXXXXXX";
char cACELEROZ[8] = "XXXXXXX";

/* Cansat liberado */
char cCANSAT_LIBERADO[3] = "X";
int CANSAT_LIBERADO = 0;

/* Sensor MQ7 */
char cMQ7[8] = "XXXX";
float MQ7[15] = {};
uint8_t flag_MQ7 = 0;
uint8_t lecturas_MQ7 = 0;       /*< Cuenta posicion de lecturas guardadas MQ7 */
uint8_t flag_guardaMQ7 = 0;
uint8_t mandar_MQ7 = 0;         /*< Cuenta posicion de lecturas mandadas MQ7 */

/* Sensor MQ135 */
char cMQ135[8] = "XXX";
float MQ135 = 0.0;

/* Altitud barometrica */
char cALTITUD_BAR[8] = "XXXX";
float ALTITUD_BAR = 0.0;

/* Temperatura exterior */
char cTEMP_EXTER[8] = "XXX";
float TEMP_EXTER = 0.0;

/* Presion barometrica */
char cPRESION_BAR[8] = "XXXX";
float PRESION_BAR = 0;

/*Prioridad tareas*/
portBASE_TYPE  prioridad1, prioridad2, prioridad3, prioridad4;
/* -------------------------------- */

void Preparar_Paquetes(void){

    /* Convertir datos float a string
     * NOTA IMPORTANTE: El RTOS no funciona con
     * sprintf( buf, "%f", (float)100.0 ); */

    /* NUMERO DE PAQUETES:  3*/
    ftoa(dN_PAQ, N_PAQ, 0);

    if(datos_ok2==1){
        /* ALTITUD BAROMETRICA: 4 */
        ftoa(ALTITUD_BAR, cALTITUD_BAR, 2);

        /* PRESION BAROMETRICA: 5 */
        ftoa((float)PRESION_BAR, cPRESION_BAR, 0);

        /* TEMPERATURA EXTERNA: 8 */
        ftoa(TEMP_EXTER, cTEMP_EXTER, 1);
    }

    /* VOLT DE LA BATERIA:  6 */
    ftoa(VOLT_BAT, cVOLT_BAT, 2);

    /* CALIDAD AIRE:        9 */
    if( flag_guardaMQ7 ){
        ftoa( MQ7[ mandar_MQ7 % 15 ], cMQ7, 2);
        mandar_MQ7++;

        /* Reiniciar variables despues de 15 datos */
        if( mandar_MQ7 > 15 ){
            mandar_MQ7 = 0;
            flag_guardaMQ7 = 0;
        }
        else{}

    }
    else{
        /* No existen datos de MQ7 mandar 0 */
        ftoa( 0.0, cMQ7, 1);
    }

    /* MONOX CARBONO:       10 */
    ftoa( MQ135, cMQ135, 2);

    /* LONGITUD:            12,13 */
    ftoa(xGPSdata.dLong, cDegLON, 0);
    ftoa(xGPSdata.mLong, cMinLON, 5);

    /* LATITUD:             14,15 */
    ftoa(xGPSdata.dLat, cDegLAT, 0);
    ftoa(xGPSdata.mLat, cMinLAT, 5);

    /* ALTITUD:             16 */
    ftoa(xGPSdata.Alt, cALT, 1);

    /* NUMERO DE SATELITES: 17 */
    ftoa(xGPSdata.nSats, cNSATS, 0);

    /* Los datos son adquiridos correctamente */
    if( datos_ok == 1 ){
        /* TEMPERATURA INTERNA: 7 */
        ftoa(TEMP_INTER, cTEMP_INTER, 1);
        /* ACELEROTMETRO:       18,19,20 */
        ftoa(acelerometroxyz[0], cACELEROX,2);
        ftoa(acelerometroxyz[1], cACELEROY,2);
        ftoa(acelerometroxyz[2], cACELEROZ,2);

        /* MAGNETOMETRO:        21,22,23 */
        ftoa(magnetometroxyz[0], cMAGNETOX, 2);
        ftoa(magnetometroxyz[1], cMAGNETOY, 2);
        ftoa(magnetometroxyz[2], cMAGNETOZ, 2);

        /* Reiniciar variable datos_ok */
        datos_ok=0;
    }

    /* TIEMPO:              24 */
    ftoa(fMISION_TIMER, MISION_TIMER, 0);

    /* CANSAT LIBRE:        25 */
    ftoa(CANSAT_LIBERADO, cCANSAT_LIBERADO, 0);

    /* Enviar cadena tipo Kansat */
        buff_size = sprintf (command,
                       "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s;\r\n\0",
                     /* 01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25; */
                           "KAANSATQRO",        /* Nombre Equipo:   1 */
                           "666",              /* No Equipo:       2 */
                           N_PAQ,               /* Paq enviados:    3 */
                           cALTITUD_BAR,        /* Altitud Bar:     4 */
                           cPRESION_BAR,        /* Presion Bar:     5 */
                           cVOLT_BAT,           /* Volt Bat:        6 */
                           cTEMP_INTER,         /* Temp Int:        7 */
                           cTEMP_EXTER,         /* Temp Ext:        8 */
                           cMQ135,              /* Calidad Aire:    9 */
                           cMQ7,                /* Monox de Carb:   10 */
                           xGPSdata.utcTime,    /* Tiempo GPS:      11 */
                           cDegLON,             /* degLongitud:     12 */
                           cMinLON,             /* minLongitud:     13 */
                           cDegLAT,             /* degLatitud:      14 */
                           cMinLAT,             /* minLatitud:      15 */
                           cALT,                /* AltitudGPS:      16 */
                           cNSATS,              /* No. SatGPS:      17 */
                           cACELEROX,           /* Acelx:           18 */
                           cACELEROY,           /* Acely:           19 */
                           cACELEROZ,           /* Acelz:           20 */
                           cMAGNETOX,           /* Magnex:          21 */
                           cMAGNETOY,           /* Magney:          22 */
                           cMAGNETOZ,           /* Magnez:          23 */
                           MISION_TIMER,        /* Uptime:          24 */
                           cCANSAT_LIBERADO     /* Cansat Liberado: 25 */
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

/* Visualiza tareas por GIO
 * @param[in]: [1,2,3,4]:   Numero de tarea
 *                     0:   Apaga todos */
void VisualizarTareas(uint8_t tarea){
    switch(tarea){
    case 0:
        /* Ver ejecucion en analizador logico */
        gioSetBit(gioPORTA, 0, 0);
        gioSetBit(gioPORTA, 1, 0);
        gioSetBit(hetPORT1, 6, 0);
        gioSetBit(hetPORT1, 8, 0);
        break;
    case 1:
        /* Ver ejecucion en analizador logico */
        gioSetBit(gioPORTA, 0, 1);
        gioSetBit(gioPORTA, 1, 0);
        gioSetBit(hetPORT1, 6, 0);
        gioSetBit(hetPORT1, 8, 0);
        break;
    case 2:
        /* Ver ejecucion en analizador logico */
        gioSetBit(gioPORTA, 0, 0);
        gioSetBit(gioPORTA, 1, 1);
        gioSetBit(hetPORT1, 6, 0);
        gioSetBit(hetPORT1, 8, 0);
        break;
    case 3:
        /* Ver ejecucion en analizador logico */
        gioSetBit(gioPORTA, 0, 0);
        gioSetBit(gioPORTA, 1, 0);
        gioSetBit(hetPORT1, 6, 1);
        gioSetBit(hetPORT1, 8, 0);
        break;
    case 4:
        /* Ver ejecucion en analizador logico */
        gioSetBit(gioPORTA, 0, 0);
        gioSetBit(gioPORTA, 1, 0);
        gioSetBit(hetPORT1, 6, 0);
        gioSetBit(hetPORT1, 8, 1);
        break;
    default:
        break;
    }

}

void hacernada(uint32 id)
{
    while(id)
    {
        id--;
    }
}
