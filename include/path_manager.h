/*
 * path_manager.h
 *
 *  Created on: 28/02/2020
 *      Author: Javier Jacal
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */

#ifndef INCLUDE_PATH_MANAGER_H_
#define INCLUDE_PATH_MANAGER_H_

#include "stdio.h"
#include "math.h"
#include "stdint.h"


unsigned int NN;        /*Position in the array*/
unsigned int waypoints;
unsigned int NN;
float pn;
float pe;
float h;
float Va;
//float alpha;
//float beta;
//float phi;
//float theta;
//float chi;
//float p;
//float q;
//float r;
//float Vg;
//float wn;
//float we;
//float psi;
float t;

unsigned int flag;
float Va_d;
float r[3];
float q[3];
float q2[3];
float c[3];
float rho;
float lambda;

float out[7];

/*--------------------------------
// *         Funciones path_manager
// *--------------------------------*/
float norm( float *q);


/* ------- PATH_MANAGER------- */

#endif /* INCLUDE_PATH_MANAGER_H_*/

