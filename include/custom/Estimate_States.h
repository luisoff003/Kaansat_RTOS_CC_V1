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
 * Estimate_States.h
 *
 *  Created on: 05/03/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_ESTIMATE_STATES_H_
#define INCLUDE_CUSTOM_ESTIMATE_STATES_H_


/* Standard libraries */
#include "math.h"
#include "stdlib.h"

/* Matrix Library */
#include "custom/CMatrixLib_V_01.h"

/* Other Libraries */
#include "custom/Utilities.h"

#define g_accel   9.80665       /* Gravity acceleration value */


/* Euler Angles */
typedef struct{
    float phi;  /*< Roll angle */
    float psi;  /*< Yaw angle */
    float theta;/*< Pitch angle */
}EulerAngles_t;

typedef struct{
    float p;
    float q;
    float r;
}Gyro_t;

/* Wind parameters */
typedef struct{
    float wn;
    float we;
}Wind_t;

/* Estimates States X */
extern float X_pn;
extern float X_pe;
extern float Vg;
extern float chi;
extern float wn;
extern float we;
extern float psi;

extern float Va;

/* Output measurements Y_GPS */
extern float yGPS_n;
extern float yGPS_e;
extern float yGPS_Vg;
extern float yGPS_chi;
extern float yGPS_wn;
extern float yGPS_we;

/* Euler Angles */
extern EulerAngles_t A;

/* Creates matrix and allocates space for data */
int Create_Matrix( char* string, float *data, int height, int width, matrix_float *Matrix );

/* Update X_GPS States */
int Fx_GPS( void );

/* Update Jacobian of F(x,u)
 * NOTE: Must be called after Fx update. */
int Update_Jacobian_Fx_GPS( void );

/* Continuous-discrete Extended Kalman Filter */
int Discrete_Extended_KalmanFilter(float T_out, int N, matrix_float *Xhat, matrix_float Fx, matrix_float JFx,
                          matrix_float Jhx, matrix_float *P, matrix_float Q, matrix_float R);

/* Low Pass Filter */
float LPF(float old, float u, float alpha);

#endif /* INCLUDE_CUSTOM_ESTIMATE_STATES_H_ */
