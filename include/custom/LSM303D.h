/*
 * LSM303D.h
 *
 *  Created on: 19/09/2019
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_LSM303D_H_
#define INCLUDE_CUSTOM_LSM303D_H_


#include "spi.h"

/* giroscopio y acelerometro */
#define leer 0x8000
#define escribir 0x0000
/* Acelerometro Magnetometro y temperatura LSM303D */
#define CTRL0_LSM303D 0x1F00
#define CTRL1_LSM303D 0x2000
#define CTRL2_LSM303D 0x2100
#define CTRL3_LSM303D 0x2200
#define CTRL4_LSM303D 0x2300
#define CTRL5_LSM303D 0x2400
#define CTRL6_LSM303D 0x2500
#define CTRL7_LSM303D 0x2600

typedef enum {
    kLSM303D_Temperatura = 1,
    kLSM303D_Acelerometro = 2,
    kLSM303D_Magnetometro = 3
} LSM303D_ModoLectura;

extern spiDAT1_t   SPI2_data_configCh1;
extern spiDAT1_t   SPI2_data_configCh0;
extern spiDAT1_t   SPI1_data_configCh0;
extern uint16 ComandoSPI[4];
extern uint16 DatoSPI01[4];
extern uint16 DatoSPI02[4];
extern uint16 DatoSPI03[4];
extern uint16 DatoSPI04[4];
extern uint16 DatoSPI05[4];
extern uint16 DatoSPI06[4];
extern uint16 RxDataSPI[30];
extern uint16 TxDataSPI[30];

/* Configurar Sensor LSM303D SPI */
void LSM303D_config_(spiBASE_t *spiREGISTRO, spiDAT1_t *SPIconfig);

/* Leer sensor LSM303D:
 * 1: Leer temperatura
 * 2: Leer magnetometro
 * 3: Leer acelerometro */
float LSM303D_READ_(unsigned int TEMP_ACEL_MAGN, spiBASE_t *spiREGISTRO, spiDAT1_t *SPIconfig, float *DataOut);

void LSM303D_Init();

#endif /* INCLUDE_CUSTOM_LSM303D_H_ */
