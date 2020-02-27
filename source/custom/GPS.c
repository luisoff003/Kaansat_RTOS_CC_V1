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
 * GPS.c
 *
 *  Created on: 26/08/2019
 *      Author: Luison
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */

#include "custom/GPS.h"
/*
 * Estados para Automaton Search
 */
enum xAutomatonStates{
    state_GPGGA =   0,
    state_G1,
    state_P,
    state_G2,
    state_G3,
    state_A,
    state_C1,
    state_Time,
    state_C2,
    state_Lat,
    state_C3,
    state_NS,
    state_C4,
    state_Long,
    state_WE,
    state_C6,
    state_C7,
    state_nSat,
    state_C8,
    state_C9,
    state_MSL,
    state_MSLd
};

    /* Iniciar variables */
/*
 *  Contadores Automaton Search [0-255]
 */
static uint8_t s_GPS = 0, s_lat = 0, s_long = 0, s_time = 0, s_nSats = 0, s_alt = 0;

/*
 * Variable temporal para guardar altura.
 */
static char c_alt[5] = {'0','0','0','0','0'};

/*--------------------------------
 *    Variables globales GPS
 *--------------------------------*/
/* Variable datos de GPS actual */
xGPGGA xGPSdata = {"X",0,0.0,0.0,0,0.0,0,0,0.0};

/* Variable datos de GPS temporal */
xGPGGA xGPSn;

/*
 *  Zona UTM
 */
//static uint8_t Zone = 0;

/* ------------ Definir funciones ------------ */

/** @fn bool getData_GPS( xGPGGA *xGPSdata, unsigned char GPGGA_char )
*   @brief Obtiene datos de trama de GPS tipo GPGGA descartando las tramas
*   incompletas o indeseables, usando el algoritmo de automaton search.
*   @param[in] xGPSdata:    pointer tipo xGPsdata en donde guardar datos
*   @param[in] pGPGGA_char: char actual recibido por el GPS.
*   @return La funcion retornara el estado de la cadena
*           - 1: La cadena esta completa, todos los datos correctos.
*           - 0: Error, la cadena esta incompleta.
*
* Recibe un char con el dato actual de una trama GPS, indentifica la trama
* obteniendo los datos de la trama GPGGA, guarda en la estructura los
* diferentes datos.
*   $GPGGA,182843.00,2037.47253,N,10011.25237,W,1,04,3.25,1923.8,M,-8.5,M,,*6A
*       Sentence Identifier:    $GPGGA,
*       Time UTC:               170834,
*       Latitude:               4123.8963,N,
*       Longitude:              08151.6838,W,
*       Fix Quality:            1,
*           0 = Invalid
*           1 = GPS fix
*           2 = DGPS fix
*       Number of Satellites:   03,
*       Horizontal Dilution:    1.5,
*       Altitude:               1952.8,
*
*   @note Para obtener datos GPGGA son necesarion al menos 04 satelites, tarda
*   alrededor de 30-40[s] en sincronizarse con 4 satelites.
*/
uint8_t getData_GPS( xGPGGA *pGPSdata, unsigned char GPGGA_char ){
    int xStatus = 0, i = 0;
    /* Automaton String Search */
    switch(GPGGA_char){
    case '$':
        if(s_GPS == state_GPGGA){
            s_GPS++;
        }
        break;
    case 'g':
    case 'G':
        if( s_GPS == state_G1 || s_GPS == state_G2 || s_GPS == state_G3 ){
            s_GPS++;
        }
        else{
//            s_GPS = 0;
        }
        break;
    case 'p':
    case 'P':
        if(s_GPS == state_P){
            s_GPS++;
        }
        else{
//            s_GPS = 0;
        }
        break;
    case 'a':
    case 'A':
        if(s_GPS == 5){
            s_GPS++;
        }
        else{
//            s_GPS = 0;
        }
        break;

    case ',':
        if(s_GPS == 6 ||s_GPS == 8||s_GPS == 10||s_GPS == 12||
                s_GPS == 15||s_GPS == 16||s_GPS == 18||s_GPS == 19){
            s_GPS ++;
        }
        else{
        //  s_GPS = 0;
        }
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
            /* -------- UTC Time -------- */
        if( s_GPS == 7 ){
            if(s_time < 8){
                pGPSdata->utcTime[s_time++] = GPGGA_char;
            }
            else{
                s_time = 0;
                s_GPS = 8;
            }
        }
            /* -------- Latitude -------- */
        else if( s_GPS == 9 ){
            switch(s_lat){
            /*Degrees*/
            case 0:
                pGPSdata->dLat = ((int)GPGGA_char-'0')*10;
                s_lat++;
                break;
            case 1:
                pGPSdata->dLat += ((int)GPGGA_char-'0');
                s_lat++;
                break;
                /* Minutes */
            case 2:
                pGPSdata->mLat = (float)(((float)GPGGA_char-'0')*10);
                s_lat++;
                break;
            case 3:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0'));
                s_lat++;
                break;
            case 4:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0')*0.10);
                s_lat++;
                break;
            case 5:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0')*0.010);
                s_lat++;
                break;
            case 6:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0')*0.0010);
                s_lat++;
                break;
            case 7:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0')*0.00010);
                s_lat++;
                break;
            case 8:
                pGPSdata->mLat += (float)(((float)GPGGA_char-'0')*0.000010);
                s_lat = 0;
                s_GPS = 10;
                break;
            }
        }

            /* -------- Longitude -------- */
        else if( s_GPS == 13 ){
            switch(s_long){
            /* Degrees */
            case 0:
                pGPSdata->dLong = ((int)GPGGA_char-'0')*100;
                s_long++;
                break;
            case 1:
                pGPSdata->dLong += ((int)GPGGA_char-'0')*10;
                s_long++;
                break;
            case 2:
                pGPSdata->dLong += ((int)GPGGA_char-'0');
                s_long++;
                break;
            /* Minutes */
            case 3:
                pGPSdata->mLong = (float)(((float)GPGGA_char-'0')*10);
                s_long++;
                break;
            case 4:
                pGPSdata->mLong += (float)(((float)GPGGA_char-'0'));
                s_long++;
                break;
            case 5:
                pGPSdata->mLong += (float)( ( (float)GPGGA_char-'0' )* 0.10 );
                s_long++;
                break;
            case 6:
                pGPSdata->mLong += (float)(((float)GPGGA_char-'0')*0.010);
                s_long++;
                break;
            case 7:
                pGPSdata->mLong += (float)(((float)GPGGA_char-'0')*0.0010);
                s_long++;
                break;
            case 8:
                pGPSdata->mLong += (float)(((float)GPGGA_char-'0')*0.00010);
                s_long++;
                break;
            case 9:
                pGPSdata->mLong += (float)(((float)GPGGA_char-'0')*0.000010);
                s_long = 0;
                s_GPS ++;
                break;
            }
        }
            /* -------- Satellites used -------- */
        else if( s_GPS == 17 ){
            if(s_nSats == 0){
                pGPSdata->nSats = ((int)GPGGA_char-'0')*10;
                s_nSats++;
            }
            else if(s_nSats == 1){
                pGPSdata->nSats += (int)GPGGA_char-'0';
                s_nSats = 0;
                s_GPS++;
            }
        }
            /* -------- MSL Altitude -------- */
        if(s_GPS == 20){
            c_alt[s_alt++] = GPGGA_char;
        }
        if(s_GPS == 21){
            c_alt[s_alt] = GPGGA_char;
            pGPSdata->Alt = 0.0;
            i = s_alt;
            for(i=0;i<s_alt;i++){
                pGPSdata->Alt += (int)(c_alt[i]-'0')*pow(10.0,(float)(s_alt-i-1) );
            }
            pGPSdata->Alt+= ((float)(c_alt[s_alt]-'0')*0.1);
            s_alt = 0;
            s_GPS = 0;
            xStatus = 1;
        }

        break;
    case '.':
            /* -------- UTC Time -------- */
        if( s_GPS == 7 ){
            if(s_time < 8){
                pGPSdata->utcTime[s_time++] = GPGGA_char;
            }
        }
            /* -------- MSL Altitude -------- */
        if( s_GPS == 20 ){
            s_GPS++;
        }

        break;
    case 'n':
    case 'N':
        if(s_GPS == 11){
            pGPSdata->Lat = (double)pGPSdata->dLat + (double)pGPSdata->mLat/60.0;
            s_GPS++;
        }
        break;
    case 's':
    case 'S':
        if(s_GPS == 11){
            pGPSdata->dLat = -pGPSdata->dLat;
            pGPSdata->mLat = -pGPSdata->mLat;
            pGPSdata->Lat = (double)pGPSdata->dLat + (double)pGPSdata->mLat/60.0;
            s_GPS++;
        }
        break;
    case 'e':
    case 'E':
        if(s_GPS == 14){
            pGPSdata->Long = (double)pGPSdata->dLong + (double)pGPSdata->mLong/60.0;
            s_GPS++;
        }
        break;
    case 'w':
    case 'W':
        if( s_GPS == 14 ){
            pGPSdata->mLong = -pGPSdata->mLong;
            pGPSdata->dLong = -pGPSdata->dLong;
            pGPSdata->Long = (double)pGPSdata->dLong + (double)pGPSdata->mLong/60.0;
            s_GPS++;
        }
        break;
    case 'm':
    case 'M':
        break;
    case '*':
        break;
    default:
        s_GPS = 0;
        xStatus = 0;
        break;
    }
    return xStatus;
}


