/*
 * param.c
 *
 *  Created on: 26/08/2019
 *      Author: Javier Jacal
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 */
#include "param.h"

Param P;
void InitParam(Param *P){
    /*gravity*/
    P->gravity = 9.80665;
    /*Physical parameters of airframe*/
    P->mass = 13.5;       /* Kg */
    P->Jx    =   0.8244;     /*Kg m^2*/
    P->Jy    =   1.135;      /*Kg m^2*/
    P->Jz    =   1.759;      /*Kg m^2*/
    P->Jxz   =   0.1204;     /*Kg m^2*/

        /*Aerodynamic coefficients*/
    P->S_wing        = 0.55;     /*Wing surface [m^2]*/
    P->b             = 2.8956;   /*span [m]*/
    P->c             = 0.18994;  /*cord [m]*/
    P->S_prop        = 0.2027;   /*Area swept out by the propeller m^2*/
    P->rho           = 1.2682;   /*Air density kg/m^3*/
    P->k_motor       = 80;       /*Linear relationship between the
    pulse-width-modulation command (δt) and the anguPlar velocity of the
    propeller */
    P->k_T_P         = 0;        /*Propeller Torque constant*/
    P->k_Omega       = 0;        /*Propeller speed constant*/
    P->e             = 0.9;      /* constant */

        /*Longitudinal Coefficients*/
    P->C_L_0         = 0.28;
    P->C_D_0         = 0.03;
    P->C_m_0         = -0.02338;
    P->C_L_alpha     = 3.45;
    P->C_D_alpha     = 0.30;
    P->C_m_alpha     = -0.38;
    P->C_L_q         = 0.0;
    P->C_D_q         = 0.0;
    P->C_m_q         = -3.6;
    P->C_L_delta_e   = -0.36;
    P->C_D_delta_e   = 0.0;
    P->C_m_delta_e   = -0.5;
    P->C_prop        = 1.0;
    P->M             = 50;
    P->alpha0        = 0.4712;
    P->epsilon       = 0.1592;
    P->C_D_p         = 0.0437;
    P->C_n_delta_r   = -0.032;

        /*Lateral Coefficients*/
    P->C_Y_0         = 0.0;
    P->C_ell_0       = 0.0;
    P->C_n_0         = 0.0;
    P->C_Y_beta      = -0.98;
    P->C_ell_beta    = -0.12;
    P->C_n_beta      = 0.25;
    P->C_Y_p         = 0.0;
    P->C_ell_p       = -0.26;
    P->C_n_p         = 0.022;
    P->C_Y_r         = 0.0;
    P->C_ell_r       = 0.14;
    P->C_n_r         = -0.35;
    P->C_Y_delta_a   = 0.0;
    P->C_ell_delta_a = 0.08;
    P->C_n_delta_a   = 0.06;
    P->C_Y_delta_r   = -0.17;
    P->C_ell_delta_r = 0.105;

    /* wind parameters*/
    P->wind_n = 0;
    P->wind_e = 0;
    P->wind_d = 0;
    P->L_u = 200;
    P->L_v = 200;
    P->L_w = 50;
    P->sigma_u = 1.06;
    P->sigma_v = 1.06;
    P->sigma_w = .7;

    /* compute trim conditions using 'mavsim_chap5_trim.slx'*/
    // initial airspeed
    P->Va0 = 35;
    P->gamma = 0; //5*pi/180;  // desired flight path angle (radians)
    P->R     = 250; //150;     // desired radius (m) - use (+) for right handed orbit, can't be 0

    /* autopilot sample rate */
    P->Ts = 0.01;
    P->tau = 0.5;

        /* first cut at initial conditions*/
    P->pn0    = 0;  // initial North position
    P->pe0    = 0;  // initial East position
    P->pd0    = 0;  // initial Down position (negative altitude)
    P->u0     = P->Va0; // initial velocity along body x-axis
    P->v0     = 0;  // initial velocity along body y-axis
    P->w0     = 0;  // initial velocity along body z-axis
    P->phi0   = 0;  // initial roll angle
    P->theta0 = 0;  // initial pitch angle
    P->psi0   = 0;  // initial yaw angle
    P->p0     = 0;  // initial body frame roll rate
    P->q0     = 0;  // initial body frame pitch rate
    P->r0     = 0;  // initial body frame yaw

    /* autopilot guidance model coefficients(chapter 9)*/
    float wn_h = 1.5;//2.4;
    float zeta_h = 0.707;//0.21;
    P->b_hdot = 2 * zeta_h * wn_h;
    P->b_h = pow(wn_h,2);

    float wn_chi = 2;//0.7;
    float zeta_chi = 0.15;//0.707;
    P->b_chidot = 2 * zeta_chi * wn_chi;
    P->b_chi = pow(wn_chi,2);
    P->b_phi= 100;//0.1;
    P->b_Va = 1;
    P->gamma_max = 45*M_PI/180;

    /* chapter 10 parameters*/
    P->k_path = 0.001;//0.05;
    P->chi_inf = 40*M_PI/180;
    P->k_orbit = 0.01;
}

void compute_gains()
{

}
