/*
 * guidance_model.h
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

typedef struct{
    float NumContStates;   //Number of continuous states
    float NumDiscStates;   //Number of discrete states
    float NumOutputs;      //Number of outputs
    float NumInputs;       //Number of inputs
    float DirFeedthrough;  //Flag for direct feedthrough
    float NumSampleTimes;  //Number of sample times
}simsizes;

float x0[7];
float ts[2];
float out[16];
/*--------------------------------
 *    Global Variables guidance_model
 *--------------------------------*/
extern simsizes sizes;
extern float out[16];

/*--------------------------------
// *     Functions guidance_model
// *--------------------------------*/
float* guidance_model(float t,float *x,float *u,int flag,float P);

void  mdlInitializeSizes(float *sys );

void Struct2Vector(float *arreglo,simsizes estructura);

void mdlDerivatives(float t,float *x,float *u,float *sys);

void mdlUpdate(float t,float *x,float *u,float*);

void mdlOutputs(float t,float *x,float *u,float*);

void mdlGetTimeOfNextVarHit(float t,float *x,float *u,float*);

void mdlTerminate(float t,float *x,float *u,float*);


/* ------- GUIDINCE MODEL------- */

#endif /* INCLUDE_GUIDANCE_MODEL_H_*/
