/*
 * path_follow.h
 *
 *  Created on: 28/02/2020
 *      Author: Javier Jacal
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */

#ifndef INCLUDE_PATH_FOLLOW_H_
#define INCLUDE_PATH_FOLLOW_H_

#include "stdio.h"
#include "math.h"
#include "stdint.h"

#include "custom/Estimate_States.h"

  float Va_d;
  float r_path[3];
  float q_path[3];
  float c_orbit[3];
  float rho_orbit;
  float lam_orbit;
//  float pn;       /* Se definio en Estimate States */
//  float pe;       /* Se definio en Estimate States */
  float h;
//  float Va;       /* Se definio en Estimate States */
  //float alpha;
  //float beta;
  float phi;
  float theta;
//  float chi;    /* Se definio en Estimate States */
  //float p;
  //float q;
  //float r2;
  //float Vg;
  //float wn;
  //float we;
  //float psi;
  float t;

  float e_p[3];
  float aux[3];
  float n[3];
  float s[3];
  float h_c;
  float chi_q;
  float e_py;
  float chi_c;
  float phi_ff;
  float d;
  float barphi;
  float Va_c;

/*--------------------------------
// *         Funciones path_manager
// *--------------------------------*/
float norm( float *q);

float* path_follow(float *in);

void cross( float *a, float *b,float *c);

float dot( float *a, float *b);

void copy_array(float *a,float *b);


/* ------- PATH_MANAGER------- */

#endif /* INCLUDE_PATH_MANAGER_H_*/
