/*
 * path_manager_chap10.c
 *
 *  Created on: 28/02/2020
 *      Author: Javier Jacal
 *      Ka'An Sat Team
 *      Universidad Aeronautica en Queretaro
 *
 *  output is:
 *  flag - if flag==1, follow waypoint path
 *      if flag==2, follow orbit

 *  Va^d - desired airspeed
 *  r    - inertial position of start of waypoint path
 *  q    - unit vector that defines inertial direction of waypoint path
 *  c    - center of orbit
 *  rho  - radius of orbit
 *  lambda = direction of orbit (+1 for CW, -1 for CCW)
 */

#include <stdio.h>
#include <stdlib.h>
#include "param.h"
#include "path_manager.h"
#include "custom/Estimate_States.h"

float* path_manager(float *in){
    int i = 0;
    NN = 0;
    waypoints = in[1+NN];
    NN = NN + 1;
    pn        = in[1+NN];
    pe        = in[2+NN];
    h         = in[3+NN];
    Va        = in[4+NN];
    // alpha   = in[5+NN];
    // beta    = in[6+NN];
    // phi     = in[7+NN];
    // theta   = in[8+NN];
    // chi     = in[9+NN];
    // p       = in[10+NN];
    // q       = in[11+NN];
    // r       = in[12+NN];
    // Vg      = in[13+NN];
    // wn      = in[14+NN];
    // we      = in[15+NN];
    // psi     = in[16+NN];
    NN = NN + 16;
    t         = in[1+NN];

    if (waypoints==0){
    // define waypoint path
        flag   = 1;
        Va_d   = 35;
        r[0] = 0;
        r[1] = 0;
        r[2] = -100;
        q[0] = -0.5;
        q[1] = -1;
        q[2] = -0.05;
        for(i=0;i<3;i++)
            q[i]    =   q[i]/norm(q);
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;      //  not used for waypoint path
        rho    = 0;             //  not used for waypoint path
        lambda = 0;             // not used for waypoint path
       }
    else{
      /*  define orbit  */
        flag   = 2;
        Va_d   = 35;            // desired airspeed
        r[0] = 0;
        r[1] = 0;
        r[2] = 0;               // not used for orbit
        q[0] = 1;
        q[1] = 0;
        q[2] = 0;               // not used for orbit
        for(i=0;i<3;i++)
            q[i] = q[i]/norm(q);
        c[0] = 1;
        c[1] = 1;
        c[2] = -100;         // center of orbit
        rho    = 400;           // radius of orbit
        lambda = 1;             //  direction of orbit
       }

    out[0] = flag;
    out[1] = Va_d;
    for(i=2;i<5;i++)
        out[i] = r[i-2];
    for(i=5;i<8;i++)
        out[i] = q[i-2];
    for(i=8;i<11;i++)
        out[i] = c[i-2];
    out[11] = rho;
    out[12] = lambda;

    return(out);

}
float norm( float *q){
    return(sqrt(pow(q[0],2)+pow(q[1],2)+pow(q[2],2)));
}
