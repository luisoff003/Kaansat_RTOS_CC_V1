/*
* guidance_model.c
*  - follow straight line path or orbit
*
*  Created on: 28/02/2020
*      Author: Javier Jacal
*      Ka'An Sat Team
*      Universidad Aeronautica en Queretaro
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "param.h"
#include "guidance_model.h"

float out[16];
simsizes sizes;

float* guidance_model(float t,float *x,float *u,int flag,float P)
{
    //float out[5];
    float sys[16];
    int i;
    switch(flag)
    {
      /*****************
      * Initialization *
      ******************/
      case 0:
        //[sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes(P);
        mdlInitializeSizes(sys);
      /**************
      * Derivatives *
      **************/
      case 1:
        mdlDerivatives(t,x,u,sys);
        break;

      /*********
      * Update *
      *********/
      case 2:
        mdlUpdate(t,x,u,sys);
        break;

      /**********
      * Outputs *
      **********/
      case 3:
        mdlOutputs(t,x,u,sys);
        break;

      /**********************
      * GetTimeOfNextVarHit *
      **********************/
      case 4:
        mdlGetTimeOfNextVarHit(t,x,u,sys);
        break;

      /************
      * Terminate *
      ************/
      case 9:
        mdlTerminate(t,x,u,sys);
        break;

      /*******************
      * Unexpected flags *
      *******************/
      default:
          printf("Error");
        break;

    /// end sfuntmpl
    }

    for(i=0;i<16;i++)
        out[i] = sys[i];

    return(out);
}

/*=============================================================================
* mdlInitializeSizes
* Return the sizes, initial conditions, and sample times for the S-function.
*=============================================================================*/

void  mdlInitializeSizes(float* sys)
{
    int i;
    /*
    * call simsizes for a sizes structure, fill it in and convert it to a
    * sizes array.
    *
    * Note that in this example, the values are hard coded.  This is not a
    * recommended practice as the characteristics of the block are typically
    * defined by the S-function parameters.
    */
    sizes.NumContStates  = 7;
    sizes.NumDiscStates  = 0;
    sizes.NumOutputs     = 16+12;
    sizes.NumInputs      = 4;//3;
    sizes.DirFeedthrough = 0;
    sizes.NumSampleTimes = 1;   // at least one sample time is needed

    Struct2Vector(sys,sizes);

    /*
    * initialize the initial conditions
    */
    x0[0] = P.pn0;
    x0[1] = P.pe0;    // initial East position
    x0[2] = P.psi0;   // initial heading
    x0[3] = 0;        // initial heading rate
    x0[4] = -P.pd0;   // initial altitude
    x0[5] = 0;        // initial climb rate
    x0[6] = P.Va0;    // initial airspeed

    /*
    * str is always an empty matrix
    */
    //str = {};

    /*
    * initialize the array of sample times
    */
    ts[0] = 0;
    ts[1] = 0;

    /* Specify the block simStateCompliance. The allowed values are:
    %    'UnknownSimState', < The default setting; warn and assume DefaultSimState
    %    'DefaultSimState', < Same sim state as a built-in block
    %    'HasNoSimState',   < No sim state
    %    'DisallowSimState' < Error out when saving or restoring the model sim state*/
    //simStateCompliance = "UnknownSimState";
    for(i=0;i<16;i++)
        out[i] = sys[i];
}
/// end mdlInitializeSizes

void Struct2Vector(float *arreglo,simsizes estructura)
{
    arreglo[0] = estructura.NumContStates;
    arreglo[1] = estructura.NumDiscStates;
    arreglo[2] = estructura.NumOutputs;
    arreglo[3] = estructura.NumInputs;
    arreglo[4] = estructura.DirFeedthrough;
    arreglo[5] = estructura.NumSampleTimes;
}

/*
*=============================================================================
* mdlDerivatives
* Return the derivatives for the continuous states.
*=============================================================================
*/
void mdlDerivatives(float t,float *x,float *u,float* sys)
{
    float pn     = x[1]; // North position
    float pe     = x[2]; // East position
    float chi    = x[3]; // heading
    float chidot = x[4]; // heading rate
    float h      = x[5]; // altitude
    float hdot   = x[6]; // climb rate
    float Va     = x[7]; // airspeed
    float Va_c   = u[1]; // commanded airspeed
    float h_c    = u[2]; // commanded altitude
    float chi_c  = u[3]; // commanded heading angle
    float phi_ff = u[4]; // feedforward roll command

    /*compute chi_c_dot from roll feedforward*/
    float chi_c_dot = P.gravity/Va*tan(phi_ff);
    //chi_c_dot = 0;
    /* solve for heading and groundspeed*/
    float psi = chi - asin( (-P.wind_n*sin(chi)+P.wind_e*cos(chi))/Va );
    //Vg  = [cos(chi), sin(chi)]*(Va*[cos(psi); sin(psi)] + [wn; we]);

    /* compute groundspeed  */
    float pndot   = Va*cos(psi) + P.wind_n;
    float pedot   = Va*sin(psi) + P.wind_e;
    float chiddot = P.b_chidot*(chi_c_dot-chidot) + P.b_chi*(chi_c-chi);
    float Vadot   = P.b_Va*(Va_c-Va);

    // don't let climb rate exceed Va*sin(\gamma_max)
    float hddot   = -P.b_hdot*hdot + P.b_h*(h_c-h);
    if ((hdot>=Va*sin(P.gamma_max)) & (hddot>0)){
        hddot = 0;
    }
    else if ((hdot<=-Va*sin(P.gamma_max)) & (hddot<0)){
        hddot = 0;
    }
    sys[0] =  pndot;
    sys[1] =  pedot;
    sys[2] =  chidot;
    sys[3] =  chiddot;
    sys[4] =  hdot;
    sys[5] =  hddot;
    sys[6] =  Vadot;
}
/// end mdlDerivatives

/*
*=============================================================================
* mdlUpdate
* Handle discrete state updates, sample time hits, and major time step
* requirements.
*=============================================================================
*/
void mdlUpdate(float t,float *x,float *u,float* sys)
{
    int i;
    for(i=0;i<7;i++)
    sys[i] = 0;
}
/// end mdlUpdate

/*
*=============================================================================
* mdlOutputs
* Return the block outputs.]
*=============================================================================
*/
void mdlOutputs(float t,float *x,float *u,float* sys)
{
    float pn     = x[1]; // North position
    float pe     = x[2]; // East position
    float chi    = x[3]; // course
    float chidot = x[4]; // course rate
    float h      = x[5]; // altitude
    float hdot   = x[6]; // climb rate
    float Va     = x[7]; // airspeed
    float alpha  = 0;
    float beta   = 0;

    /*wind speed  */
    float wn = P.wind_n;
    float we = P.wind_e;

    /*solve for heading and groundspeed*/
    float psi = chi - asin( (-P.wind_n*sin(chi)+P.wind_e*cos(chi))/Va );

    float Vg,Vg1,Vg2;
    Vg1 = Va*cos(psi) + wn;
    Vg2 = Va*sin(psi) + we;
    Vg = cos(chi)*Vg1 + sin(chi)*Vg2; //[cos(chi), sin(chi)]*(Va*[cos(psi); sin(psi)] + [wn; we]);

    //roll angle is given by psidot = g/V*tan(phi)
    float phi     = atan(Vg*chidot/P.gravity);

    /*letting theta equal flight path angle given by hdot = V sin(gamma)*/
    float theta = asin(hdot/Va);

    /*set angular rates to zero*/
    float p     = 0;
    float q     = 0;
    float r     = 0;


    /* output the same states that are returned by the state estimation block
    *   pnhat    - estimated North position,
    *   pehat    - estimated East position,
    *   hhat     - estimated altitude,
    *   Vahat    - estimated airspeed,
    *   alphahat - estimated angle of attack
    *   betahat  - estimated sideslip angle
    *   phihat   - estimated roll angle,
    *   thetahat - estimated pitch angel,
    *   chihat   - estimated course,
    *   phat     - estimated roll rate,
    *   qhat     - estimated pitch rate,
    *   rhat     - estimated yaw rate,
    *   Vghat    - estimated ground speed,
    *   wnhat    - estimate of North wind,
    *   wehat    - estimate of East wind
    *   psihat   - estimate of heading angle
    * also need to return the normal state vector so that we don't need to
    * change the drawing routine.*/

    sys[0] =  pn;
    sys[1] =  pe;
    sys[2] =  h;
    sys[3] =  Va;
    sys[4] =  alpha;
    sys[5] =  beta;
    sys[6] =  phi;
    sys[7] =  theta;
    sys[8] =  chi;
    sys[9] =  p;
    sys[10] =  q;
    sys[11] =  r;
    sys[12] =  Vg;
    sys[13] =  wn;
    sys[14] =  we;
    sys[15] =  psi;
    sys[16] =  pn;
    sys[17] =  pe;
    sys[18] =  -h;
    sys[19] =  Va;
    sys[20] =  0;
    sys[21] =  0;
    sys[22] =  phi;
    sys[23] =  theta;
    sys[24] =  psi;
    sys[25] =  p;
    sys[26] =  q;
    sys[27] =  r;

}
/// end mdlOutputs

/*
=============================================================================
* mdlGetTimeOfNextVarHit
* Return the time of the next hit for this block.  Note that the result is
* absolute time.  Note that this function is only used when you specify a
* variable discrete-time sample time [-2 0] in the sample time array in
* mdlInitializeSizes.
*=============================================================================
*/
void  mdlGetTimeOfNextVarHit(float t,float *x,float *u,float* sys)
{
    float sampleTime = 1;    //  Example, set the next hit to be one second later.
    sys[16] = t + sampleTime;///Not sure about it//////
    /***********************************************************/
}
/// end mdlGetTimeOfNextVarHit

/*
*=============================================================================
* mdlTerminate
* Perform any end of simulation tasks.
*=============================================================================
*/
void  mdlTerminate(float t,float *x,float *u,float* sys)
{
    int i;
    for(i=0;i<7;i++)
        sys[i]=0;
}
/// end mdlTerminate
