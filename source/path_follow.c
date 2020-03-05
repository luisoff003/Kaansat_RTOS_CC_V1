/*
*path_follow.c
*  - follow straight line path or orbit
*
*  Created on: 28/02/2020
*      Author: Javier Jacal
*      Ka'An Sat Team
*      Universidad Aeronautica en Queretaro
*
* input is:
*   flag - if flag==1, follow waypoint path
*          if flag==2, follow orbit
*
*   Va^d   - desired airspeed
*   r      - inertial position of start of waypoint path
*   q      - unit vector that defines inertial direction of waypoint path
*   c      - center of orbit
*   rho    - radius of orbit
*   lambda - direction of orbit (+1 for CW, -1 for CCW)
*   xhat   - estimated MAV states (pn, pe, pd, Va, alpha, beta, phi, theta, chi, p, q, r, Vg, wn, we, psi)
*
* output is:
*  Va_c - airspeed command
*  h_c  - altitude command
*  chi_c - heading command
*  phi_ff - feed forward roll command
*/

#include <stdio.h>
#include <stdlib.h>
#include "param.h"
#include "path_follow.h"
#include "path_manager.h"

float* path_follow(float *in)
{
  unsigned int NN = 0;
  unsigned int flag = in[1+NN];
  int i = 0;
  Va_d      = in[2+NN];
  r_path[0] = in[3+NN];
  r_path[1] = in[4+NN];
  r_path[2] = in[5+NN];
  q_path[0] = in[6+NN];
  q_path[1] = in[7+NN];
  q_path[2] = in[8+NN];
  c_orbit[0] = in[9+NN];
  c_orbit[1] = in[10+NN];
  c_orbit[2] = in[11+NN];
  rho_orbit = in[12+NN];
  lam_orbit = in[13+NN];
  NN = NN + 13;
  pn        = in[1+NN];
  pe        = in[2+NN];
  h         = in[3+NN];
  Va        = in[4+NN];
  // alpha   = in[5+NN];
  // beta    = in[6+NN];
  phi       = in[7+NN];
  theta     = in[8+NN];
  chi       = in[9+NN];
  // p       = in[10+NN];
  // q       = in[11+NN];
  r2       = in[12+NN];
  // Vg      = in[13+NN];
  // wn      = in[14+NN];
  // we      = in[15+NN];
  // psi     = in[16+NN];
  NN = NN + 16;
  t         = in[1+NN];

  switch (flag){
      case 1: // follow straight line path specified by r and q
          e_p[0] = pn-r_path[0];
          e_p[1] = pe-r_path[1];
          e_p[2] = -h-r_path[2];
          float array[3] = {0,0,1};             //auxiliary array
          copy_array(cross(q_path, array),&aux);
          for(i=0;i<3;i++){
            n[i] =  aux[i]/ norm(cross(q_path, array));
          }
          s[0] = e_p[0] - dot(e_p, n)*n[0];
          s[1] = e_p[2] - dot(e_p, n)*n[3];
          s[2] = e_p[2] - dot(e_p, n)*n[3];
          h_c = -r_path[3] - sqrt(pow(s[1],2) + pow(s[2],2)) * q_path[3] / sqrt(pow(q_path[1],2)+pow(q_path[2],2));
          chi_q = atan2(q_path[2], q_path[1]);
          while(chi_q-chi < -M_PI)
              chi_q = chi_q + 2*M_PI;
          while (chi_q-chi > M_PI)
              chi_q = chi_q - 2*M_PI;
          e_py = -sin(chi_q)*(pn-r_path[1]) + cos(chi_q)*(pe-r_path[2]);

          chi_c = chi_q - P.chi_inf*2/M_PI*atan(P.k_path*e_py);

          phi_ff = 0;
      break;
      case 2: // follow orbit specified by c, rho, lam
          h_c = -c_orbit[3];
          d = sqrt(pow((pn-c_orbit[1]),2) + pow((pe-c_orbit[2]),2));
          barphi = atan2(pe-c_orbit[2], pn-c_orbit[1]);
          while(barphi-chi < -M_PI)
            barphi = barphi + 2*M_PI;
          while (barphi-chi > M_PI)
            barphi = barphi - 2*M_PI;


          chi_c = barphi + lam_orbit*(M_PI/2 + atan(P.k_orbit*(d-rho_orbit)));
          phi_ff = 0;
      break;
  }

  // command airspeed equal to desired airspeed
  Va_c = Va_d;

  // create output
    out[0] = Va_c;
    out[1] = h_c;
    out[2] = chi_c;
    out[3] = phi_ff;

    return(out);
}
float* cross( float *a, float *b){
    float cross_product[3];
    cross_product[0]=a[1]*b[2]-a[2]*b[1];
    cross_product[1]=a[2]*b[0]-a[0]*b[2];
    cross_product[2]=a[0]*b[1]-a[1]*b[0];

    return(cross_product);
}

float dot( float *a, float *b){
    float scalar_product;
    scalar_product=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];

    return(scalar_product);
}

void copy_array(float *a,float *b)
{
    int i;
    for(i=0;i<3;i++)
    b[i] = a[i];
}
