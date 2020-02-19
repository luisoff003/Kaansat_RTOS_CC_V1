/*
 * Utilidades.h
 *
 *  Created on: 27/08/2019
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_UTILIDADES_H_
#define INCLUDE_CUSTOM_UTILIDADES_H_

#include "stdint.h"
#include "stdlib.h"
#include "custom/GPS.h"
#include "gio.h"
#include "het.h"

/* Librerias RTOS */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

#define AD_VOLT_BAT     0           /*< ADIN0 de la tarjeta */
#define AD_MQ7          1           /*< ADIN1 de la tarjeta */
#define AD_MQ135        2           /*< ADIN2 de la tarjeta */

/* --------------------------------
 *  VARIABLES IMPORTANTES GLOBALES
 * -------------------------------- */
/* Buffer guarda cadena a enviar */
extern char command[255];

/* Tamano de buffer */
extern uint8_t buff_size;

/* Tiempo de mision transcurrido s */
extern float fMISION_TIMER;
extern char MISION_TIMER[6];

/* Numero de paquetes enviados */
extern int dN_PAQ ;
extern char N_PAQ[6];

/* Cadenas de GPS */
extern char cDegLAT[10] ;           /* Grados Latitud */
extern char cMinLAT[10] ;           /* Minutos Latitud */
extern char cDegLON[10] ;           /* Grados Longitud */
extern char cMinLON[10] ;           /* Minutos Longitud */
extern char cALT[7] ;               /* Altitud */
extern char cNSATS[3] ;

/* Voltaje de la bateria */
extern float VOLT_BAT;
extern char cVOLT_BAT[4];

/* Temperatura interna */
extern float TEMP_INTER;
extern char cTEMP_INTER[8];

/* Magnetometro */
extern float magnetometroxyz[3];
extern char cMAGNETOX[8];
extern char cMAGNETOY[8];
extern char cMAGNETOZ[8];

/* Acelerometro */
extern int datos_ok;
extern int datos_ok2;
extern float acelerometroxyz[3];
extern char cACELEROX[8];
extern char cACELEROY[8];
extern char cACELEROZ[8];

/* Cansat liberado */
extern char cCANSAT_LIBERADO[3];
extern int CANSAT_LIBERADO;

/* Sensor MQ7 */
extern char cMQ7[8];
extern float MQ7[15];
extern uint8_t flag_MQ7;
extern uint8_t lecturas_MQ7;        /*< Cuenta posicion de lecturas guardadas MQ7 */
extern uint8_t flag_guardaMQ7;      /*< Cuenta posicion de lecturas mandadas MQ7 */

/* Sensor MQ135 */
extern char cMQ135[8];
extern float MQ135;

/* Altitud barometrica */
extern char cALTITUD_BAR[8] ;
extern float ALTITUD_BAR ;

/* Temperatura exterior */
extern char cTEMP_EXTER[8] ;
extern float TEMP_EXTER ;

/* Presion barometrica */
extern char cPRESION_BAR[8];
extern float PRESION_BAR;

/*Prioridad tareas*/
extern portBASE_TYPE  prioridad1, prioridad2, prioridad3, prioridad4;

/* -------------------------------- */

/* Prepara los paquetes de datos a mandar.
 * Nota: En RTOS no funciona sprintf con variables tipo float.
 *       Se debe usar sprintf("%s", CADENA); */
void Preparar_Paquetes(void);

/*  Convierte float a cadenas  */
void ftoa(float n, char *res, int afterpoint);
static void reverse(char *, size_t);
size_t  sltoa(char *s, long int n);

/* Visualizar tareas en analizador logico */
void VisualizarTareas(uint8_t tarea);

void hacernada(uint32 id);

#endif /* INCLUDE_CUSTOM_UTILIDADES_H_ */
