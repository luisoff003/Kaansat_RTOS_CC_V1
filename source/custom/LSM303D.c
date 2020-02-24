/*
 * LSM303D.c
 *
 *  Created on: 19/09/2019
 *      Author: Luison
 */


#include "Custom/LSM303D.h"
#include "Custom/Utilities.h"

spiDAT1_t   SPI2_data_configCh1;
spiDAT1_t   SPI2_data_configCh0;
spiDAT1_t   SPI1_data_configCh0;
uint16 ComandoSPI[4]= {0x0,0x0,0x0,0x0};
uint16 DatoSPI01[4]= {0,0,0,0};
uint16 DatoSPI02[4]= {0,0,0,0};
uint16 DatoSPI03[4]= {0,0,0,0};
uint16 DatoSPI04[4]= {0,0,0,0};
uint16 DatoSPI05[4]= {0,0,0,0};
uint16 DatoSPI06[4]= {0,0,0,0};
uint16 RxDataSPI[30] = {};
uint16 TxDataSPI[30]= {0xA600,20000,3,4,5,6,7,8,9};

float LSM303D_READ_(const unsigned int TEMP_ACEL_MAGN, spiBASE_t *spiREGISTRO, spiDAT1_t *SPIconfig, float *DataOut)
{
    float temperatura=0.0;
    uint16 ComandoSPI[4]= {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
    uint16 DatoSPI[10]= {0,0,0,0,0,0,0,0,0,0};

    // ********************   LEEMOS STATUS del giroscopio          *****************  //
    /*
    ComandoSPI[0]=leer|0x0FFF; // byte alto registro byte bajo valor
    spiSendAndGetData(spiREG2, &SPI2_data_configCh0,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    DatoSPI[1]=DatoSPI[0];
    DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
    sciEnviarDatos(sprintf(command, "a0= %i", DatoSPI[0]),command, 0);
    sciEnviarDatos(sprintf(command, "   a1= %d", DatoSPI[1]),command, 1);
     */
    if(TEMP_ACEL_MAGN==1) // Leemos temperatura
    {
        //  ********* BEGIN  LEEMOS LA TEMPERATURA Dato bajo
        ComandoSPI[0]=leer|0x05FF; // byte alto registro byte bajo valor
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  LEEMOS LA TEMPERATURA Dato alto
        ComandoSPI[0]=leer|0x06FF; // byte alto registro byte alto valor
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x0800)==1) // el dato es negativo
        {
            DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        temperatura=25.0+((float)((short)DatoSPI[0])/8);
        //Regresamos temperatura
        return(temperatura);
    }
    if(TEMP_ACEL_MAGN==2) // Leemos aceleración
    {
        //  ********* BEGIN  LEEMOS LA aceleración X Dato bajo
        ComandoSPI[0]=leer|0x28FF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  LEEMOS LA aceleración Dato alto
        ComandoSPI[0]=leer|0x29FF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[0]=25.0+((float)((short)DatoSPI[0])/8);

        //  ********* BEGIN  LEEMOS LA aceleración Y Dato bajo
        ComandoSPI[0]=leer|0x2AFF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  LEEMOS LA aceleración Dato alto
        ComandoSPI[0]=leer|0x2BFF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[1]=25.0+((float)((short)DatoSPI[0])/8);

        //  ********* BEGIN  LEEMOS LA aceleración Z Dato bajo
        ComandoSPI[0]=leer|0x2CFF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  LEEMOS LA aceleración Dato alto
        ComandoSPI[0]=leer|0x2DFF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[2]=25.0+((float)((short)DatoSPI[0])/8);
    }
    if(TEMP_ACEL_MAGN==3) // Leemos Campo magnético
    {
        //  ********* BEGIN  LEEMOS el campo eje X Dato bajo
        ComandoSPI[0]=leer|0x08FF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  ********* BEGIN  LEEMOS el campo eje X Dato alto
        ComandoSPI[0]=leer|0x09FF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[3]=25.0+((float)((short)DatoSPI[0])/8);

        //  ********* BEGIN  LEEMOS el campo eje Y Dato bajo
        ComandoSPI[0]=leer|0x0AFF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  ********* BEGIN  LEEMOS el campo eje Y Dato alto
        ComandoSPI[0]=leer|0x0BFF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[4]=25.0+((float)((short)DatoSPI[0])/8);

        //  ********* BEGIN  LEEMOS el campo eje Z Dato bajo
        ComandoSPI[0]=leer|0x0CFF; // byte bajo
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[1]=((DatoSPI[0]) & (0x00FF));
        //  ********* BEGIN  LEEMOS el campo eje Z Dato alto
        ComandoSPI[0]=leer|0x0DFF; // byte alto
        spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
        hacernada(1000);
        DatoSPI[0]=((DatoSPI[0]) & (0x00FF));
        DatoSPI[0]=(DatoSPI[0]<<8)+DatoSPI[1];
        // revisamos si el dato es negativo
        if((DatoSPI[0]& 0x8000)==1) // el dato es negativo
        {
            //DatoSPI[0]=(DatoSPI[0] | 0xF000);
            // negamos y sumamos 1 para hacer el complemento a2
            DatoSPI[0]=DatoSPI[0] ^ 0xFFFF; // para negar hacemos xor 0 ^ 1 = 1;   1 ^ 1 =0
            DatoSPI[0]=DatoSPI[0] + 1; // hacemos el complemento a2
        }
        DataOut[5]=25.0+((float)((short)DatoSPI[0])/8);
    }
    return(0.0);
}

void LSM303D_config_(spiBASE_t *spiREGISTRO, spiDAT1_t *SPIconfig)
{
    uint16 ComandoSPI[4]= {0xFFFF,0xFFFF,0xFFFF,0xFFFF};
    uint16 DatoSPI[10]= {0,0,0,0,0,0,0,0,0,0};

    // CONFIGURACIÓN DE SENSOR DE TEMPERATURA, LO ENCENDEMOS
//    ComandoSPI[0]=escribir|0x2400|0x0094; // ENCENDEMOS, byte alto registro byte bajo valor
 //   spiSendAndGetData(spiREGISTRO, &SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
 //   hacernada(1000);

    /*  *********************   CONFIGURACION DE LSM303D   ******************   */

    // CONFIGURACIÓN DE CTRL0 #define CTRL0 0x1F00
    ComandoSPI[0]=escribir|CTRL0_LSM303D|0x0000; // ENCENDEMOS, byte alto registro byte bajo valor
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL1 #define CTRL1 0x2000
    ComandoSPI[0]=escribir|CTRL1_LSM303D|0x0067; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL2 #define CTRL2 0x2100
    ComandoSPI[0]=escribir|CTRL2_LSM303D|0x00D0; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL3 #define CTRL3 0x2200
    ComandoSPI[0]=escribir|CTRL3_LSM303D|0x0000; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL4 #define CTRL4 0x2300
    ComandoSPI[0]=escribir|CTRL4_LSM303D|0x0000; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL5 #define CTRL5 0x2400
    ComandoSPI[0]=escribir|CTRL5_LSM303D|0x00F4; // encendemos TPM, resolución y rate del magnetómetro
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL6 #define CTRL6 0x2500
    ComandoSPI[0]=escribir|CTRL6_LSM303D|0x0060; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
    // CONFIGURACIÓN DE CTRL7 #define CTRL7 0x2600
    ComandoSPI[0]=escribir|CTRL7_LSM303D|0x0080; //
    spiSendAndGetData(spiREGISTRO, SPIconfig,(uint32) 1, ComandoSPI,DatoSPI);
    hacernada(1000);
}

void LSM303D_Init(){
    /* Configuración de puerto SPI2 OJO, dos sensores a un solo puerto con CS0 y CS1 */
    SPI2_data_configCh0.CS_HOLD = FALSE;
    SPI2_data_configCh0.WDEL = TRUE;
    SPI2_data_configCh0.DFSEL = SPI_FMT_0; // antes en SPI_FMT_1: modo 2: Select the Data word format by setting DFSEL bits. Select the Number of the configured SPIFMTx register (0 to 3) to used for the communication. Note: It is highly recommended to use SPIDAT1 register, SPIDAT0 is supported for compatibility reason
    SPI2_data_configCh0.CSNR = SPI_CS_0;   // con este controlamos el slave chip select 0

    SPI2_data_configCh1.CS_HOLD=FALSE;
    SPI2_data_configCh1.WDEL=TRUE;
    SPI2_data_configCh1.DFSEL=SPI_FMT_0; // antes en SPI_FMT_1: modo 2: Select the Data word format by setting DFSEL bits. Select the Number of the configured SPIFMTx register (0 to 3) to used for the communication. Note: It is highly recommended to use SPIDAT1 register, SPIDAT0 is supported for compatibility reason
    SPI2_data_configCh1.CSNR = SPI_CS_1; // con este controlamos el slave chip select 1
}

