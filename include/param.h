/*
 * param.h
 *
 *  Created on: 26/02/2020
 *      Author: Javier Jacal
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */

#ifndef INCLUDE_PARAM_H_
#define INCLUDE_PARAM_H_

#include "stdio.h"
#include "math.h"
#include "stdint.h"
#define g 9.80665
//#define M_PI 3.1415926535

/* ------- Parameters for Delta Wing Glider ------- */
typedef struct{
    /*gravity*/
    float gravity;
    /*Physical parameters of airframe*/
    float mass;       /* Kg */

        /*Aircraft are often symmetric about the plane
         spanned by ib and kb. In that case Jxy = Jyz = 0*/

        /*Inertia matrix J*/
    float Jx;     /*Kg m^2*/
    float Jy;      /*Kg m^2*/
    float Jz;      /*Kg m^2*/
    float Jxz;     /*Kg m^2*/

        /*Aerodynamic coefficients*/
    float S_wing;     /*Wing surface [m^2]*/
    float b;   /*span [m]*/
    float c;  /*cord [m]*/
    float S_prop;   /*Area swept out by the propeller m^2*/
    float rho;   /*Air density kg/m^3*/
    float k_motor;       /*Linear relationship between the
    pulse-width-modulation command (δt) and the angular velocity of the
    propeller */
    float k_T_P;        /*Propeller Torque constant*/
    float k_Omega;        /*Propeller speed constant*/
    float e;      /* constant */

        /*Longitudinal Coefficients*/
    float C_L_0;
    float C_D_0;
    float C_m_0;
    float C_L_alpha;
    float C_D_alpha;
    float C_m_alpha;
    float C_L_q;
    float C_D_q;
    float C_m_q;
    float C_L_delta_e;
    float C_D_delta_e;
    float C_m_delta_e;
    float C_prop;
    float M;
    float alpha0;
    float epsilon;
    float C_D_p;
    float C_n_delta_r;

        /*Lateral Coefficients*/
    float C_Y_0;
    float C_ell_0;
    float C_n_0;
    float C_Y_beta;
    float C_ell_beta;
    float C_n_beta;
    float C_Y_p;
    float C_ell_p;
    float C_n_p;
    float C_Y_r;
    float C_ell_r;
    float C_n_r;
    float C_Y_delta_a;
    float C_ell_delta_a;
    float C_n_delta_a;
    float C_Y_delta_r;
    float C_ell_delta_r;

    /* wind parameters*/
    float wind_n;
    float wind_e;
    float wind_d;
    float L_u;
    float L_v;
    float L_w;
    float sigma_u;
    float sigma_v;
    float sigma_w;

    /* compute trim conditions using 'mavsim_chap5_trim.slx'*/
    // initial airspeed
    float Va0;
    float gamma; //5*pi/180;  // desired flight path angle (radians)
    float R; //150;     // desired radius (m) - use (+) for right handed orbit, can't be 0

    /* autopilot sample rate */
    float Ts;
    float tau;

    /* first cut at initial conditions*/
    float pn0;        // initial North position
    float pe0;        //initial East position
    float pd0;        // initial Down position (negative altitude)
    float u0;         // initial velocity along body x-axis
    float v0;         // initial velocity along body y-axis
    float w0;         // initial velocity along body z-axis
    float phi0;       // initial roll angle
    float theta0;     // initial pitch angle
    float psi0;       // initial yaw angle
    float p0;         // initial body frame roll rate
    float q0;         // initial body frame pitch rate
    float r0;         // initial body frame yaw rate

    /* autopilot guidance model coefficients(chapter 9)*/
    float b_hdot;
    float b_h;
    float b_chidot;
    float b_chi;
    float b_phi;
    float b_Va;
    float gamma_max;

    /* chapter 10 parameters*/
    float k_path;
    float chi_inf;
    float k_orbit;
}Param;

/*--------------------------------
 *    Variables globales param
 *--------------------------------*/
extern Param P;
/*--------------------------------
// *         Funciones param
// *--------------------------------*/
void InitParam( Param *P);

void compute_gains();

/* ------- PARAM ------- */

#endif /* INCLUDE_PARAM_H_*/
