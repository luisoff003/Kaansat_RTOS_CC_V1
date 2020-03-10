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
 * Estimate_States.c
 *
 *  Created on: 05/03/2020
 *      Author: Luison
 */
#include "custom/Estimate_States.h"

static matrix_float F_matrix;
static float F_data[7*1];      /*7x1*/

static matrix_float JF_matrix;
static float JF_data[7*7];      /*7x7*/

static matrix_float H_matrix;
static float H_data[6*1];      /*7x7*/

static matrix_float JH_matrix;
static float JH_data[6*7];      /*6x7*/

/* Estimates States X */
float X_pn = 0.0;       /*< North Position */
float X_pe = 0.0;       /*< East Position */
float Vg = 0.0;         /*< Ground Speed */
float chi = 0.0;        /*< Course angle */
float wn = 0.0;         /*< Wind speed north */
float we = 0.0;         /*< Wind speed east */
float psi = 0.0;        /*< Yaw angle */

float Va = 0.0;

/* Output measurements Y_GPS */
float yGPS_n = 0.0;        /*< Corrected North Position */
float yGPS_e = 0.0;        /*< Corrected East Position */
float yGPS_Vg = 0.0;       /*< Corrected Ground Speed */
float yGPS_chi = 0.0;      /*< Corrected Course angle */
float yGPS_wn = 0.0;       /*< Wind speed north */
float yGPS_we = 0.0;       /*< Wind speed east */

/* Euler Angles */
EulerAngles_t A = {0.0, 0.0, 0.0};

/* Gyro velocities */
Gyro_t G = {0.0, 0.0, 0.0};

/* Update States Xdot = F(x,u) */
int Update_Fx_GPS( void ){
    float psi_dot = G.q*(sin(A.phi)/cos(A.theta)) + G.r*(cos(A.phi)/cos(A.theta));
    matrix_float_set(&F_matrix, 1, 1, Vg*cos(chi) );
    matrix_float_set(&F_matrix, 2, 1, Vg*sin(chi) );
    matrix_float_set(&F_matrix, 3, 1, ((Va*cos(A.psi)+wn)*(-Va*psi_dot*sin(A.psi))+(Va*sin(A.psi)+we)*(Va*psi_dot*cos(psi))) );
    matrix_float_set(&F_matrix, 4, 1, (g_accel/Vg)*tan(A.phi)*cos(chi-A.psi) );
    matrix_float_set(&F_matrix, 5, 1, 0.0 );
    matrix_float_set(&F_matrix, 6, 1, 0.0 );
    matrix_float_set(&F_matrix, 7, 1, psi_dot );
    return 0;
}

/* Update Jacobian of F(x,u)
 * NOTE: Must be called after Fx update. */
int Update_Jacobian_Fx_GPS(void){
    float Vgdot = matrix_float_get(&F_matrix, 3, 1);
    float psi_dot = matrix_float_get(&F_matrix, 7, 1);
    matrix_float_set_all(&JF_matrix, 0.0);
    matrix_float_set(&JF_matrix, 1, 2, cos(chi));
    matrix_float_set(&JF_matrix, 1, 3,- Vg*sin(chi));
    matrix_float_set(&JF_matrix, 2, 2, sin(chi));
    matrix_float_set(&JF_matrix, 2, 3, Vg*cos(chi));
    matrix_float_set(&JF_matrix, 3, 3, -Vgdot/Vg);
    matrix_float_set(&JF_matrix, 3, 5, -psi_dot*Va*sin(psi) );
    matrix_float_set(&JF_matrix, 3, 6, psi_dot*Va*cos(psi) );
    matrix_float_set(&JF_matrix, 3, 7, -psi_dot*(Va/Vg)*( wn*cos(psi)+we*sin(A.psi) ) );
    matrix_float_set(&JF_matrix, 4, 3, -(g_accel/pow(Vg,2))*tan(A.phi)*cos(chi-A.psi) );
    matrix_float_set(&JF_matrix, 4, 4, -(g_accel/Vg)*tan(A.phi)*cos(chi-A.psi) );
    matrix_float_set(&JF_matrix, 4, 7, (g_accel/Vg)*tan(A.phi)*cos(chi-A.psi) );
    return 0;
}


/* Update States Y_GPS = H(x,u) */
int Update_Hx_GPS(void ){
    matrix_float_set(&H_matrix, 1, 1, X_pn );
    matrix_float_set(&H_matrix, 2, 1, X_pe );
    matrix_float_set(&H_matrix, 3, 1, Vg );
    matrix_float_set(&H_matrix, 4, 1, chi );
    matrix_float_set(&H_matrix, 5, 1, Va*cos(A.psi)+wn-Vg*cos(chi) );
    matrix_float_set(&H_matrix, 6, 1, Va*sin(A.psi)+we-Vg*sin(chi) );
    return 0;
}

/* Update Jacobian of H(x,u)
 * NOTE: Must be called after Hx update. */
int Update_Jacobian_Hx_GPS( void ){
    matrix_float_set_all(&JH_matrix, 0.0);
    matrix_float_set(&JH_matrix, 1, 1, 1.0);
    matrix_float_set(&JH_matrix, 2, 2, 1.0);
    matrix_float_set(&JH_matrix, 3, 3, 1.0);
    matrix_float_set(&JH_matrix, 4, 4, 1.0);
    matrix_float_set(&JH_matrix, 5, 5, 1.0);
    matrix_float_set(&JH_matrix, 6, 6, 1.0);
    matrix_float_set(&JH_matrix, 5, 3, -cos(chi));
    matrix_float_set(&JH_matrix, 5, 4, Vg*sin(chi));
    matrix_float_set(&JH_matrix, 5, 7, -Va*sin(chi));
    matrix_float_set(&JH_matrix, 6, 3, -sin(chi));
    matrix_float_set(&JH_matrix, 6, 4, -Vg*cos(chi));
    matrix_float_set(&JH_matrix, 6, 7, Va*cos(chi));
    return 0;
}

/* Low Pass Filter */
float LPF(float old, float u, float alpha){
    float hat = 0.0;
    hat = alpha*old + ( 1.0f - alpha )*u;
    return hat;
}

/* Continuous-discrete Extended Kalman Filter */
int Discrete_Extended_KalmanFilter(float T_out, int N, matrix_float *Xhat, matrix_float Fx, matrix_float JFx,
                          matrix_float Jhx, matrix_float *P, matrix_float Q, matrix_float R){
    int i = 0, j = 0;
    /* Initialize Identity Matrix */
    matrix_float I_matrix;
    float *I_data = NULL;
    Create_Matrix( "Identity", I_data , P->height, P->width, &I_matrix);

    /* Initialize Ci and Li matrixes */
    matrix_float Ci, Li, Ri;
    float *Ci_data = NULL, *Li_data = NULL, *Ri_data = NULL;
    Create_Matrix( "Ci", Ci_data , 1, P->width, &Ci);
    Create_Matrix( "Li", Li_data , 1, P->width, &Li);
    Create_Matrix( "Ri", Ri_data , 1, P->width, &Ri);

    /* Initialize Ans matrix */
    matrix_float Ans_matrix_1, Ans_matrix_2;
    float *Ans_matrix_data_1 = NULL, *Ans_matrix_data_2 = NULL;
    Create_Matrix( "Ans1 hx1", Ans_matrix_data_1 , P->height, P->width, &Ans_matrix_1);
    Create_Matrix( "Ans2 hx1", Ans_matrix_data_2 , P->height, P->width, &Ans_matrix_2);

    /* ------------ Prediction Step ------------ */
    for( i = 0; i<N; i++ ){
        /* ------------ Xhat = Xhat + (T_out/N)Fx ------------ */
        matrix_float_times( &Fx, (float)(T_out/N) );    /* (T_out/N)*Fx */
        matrix_float_add( Xhat, &Fx );                  /* Xhat + (T_out/N)*Fx */

        /* ------------ P = P + (T_out/N)(AP + PA^T + Q) ------------ */
        matrix_float_mul( &JFx, P, &Ans_matrix_1 );     /* AP */
        matrix_float_mul_trans(P, &JFx, &Ans_matrix_2); /* PA^T */
        matrix_float_add( &Ans_matrix_2, &Q );          /* PA^T + Q */
        matrix_float_add( &Ans_matrix_1, &Ans_matrix_2 );       /* AP + PA^T + Q */
        matrix_float_times(&Ans_matrix_1, (float)(T_out/N) );   /* (T_out/N)(AP + PA^T + Q) */
        matrix_float_add(P, &Ans_matrix_1);             /* P + (T_out/N)(AP + PA^T + Q) */
    }
    /* Create new Ans matrix 1xW */
    free(Ans_matrix_data_1);
    free(Ans_matrix_data_2);
    Create_Matrix( "Ans1 1x1", Ans_matrix_data_1 , 1, 1, &Ans_matrix_1);
    Create_Matrix( "Ans2 1xW", Ans_matrix_data_2 , 1, P->width, &Ans_matrix_2);

    /* ------------ Measurement Update ------------ */
    if( 1 ){        /*< Measurement has been received from sensor */
        for( i = 1; i<Jhx.height+1; i++){
            for( j = 1; j<Jhx.width+1; j++){
                /* ------------ Ci = dhi/dx(x,u) ------------ */
                matrix_float_set( &Ci, 1, j, matrix_float_get(&Jhx, i, j));
                /* ------------ Ri ------------ */
                matrix_float_set( &Ri, 1, j, matrix_float_get(&R, i, j));
            }
            /* ------------ Li = PCi^T ( Ri + CiPCi^T )^-1 ------------ */
            matrix_float_mul( &Ci, P, &Ans_matrix_1);                  /* CiP */
            matrix_float_mul_trans(&Ans_matrix_1, &Ci, &Ans_matrix_2);  /* CiPCi^T */
//            Ans_matrix_1->data[0] +=  Ri->data[i-1];                    /* Ri + CiPCi^T */
            matrix_float_mul_trans(P, &Ci, &Ans_matrix_2);             /* PCi^T */
//            matrix_float_times(&Ans_matrix_2, 1/Ans_matrix_1->data[0]); /* PCi^T(Ri + CiPCi^T)^-1 */
            matrix_float_copy(&Li, &Ans_matrix_2);
            /* Create new Ans Matrix */
            free(Ans_matrix_data_1);
            free(Ans_matrix_data_2);
            Create_Matrix( "Ans1 HxW", Ans_matrix_data_1 , P->height, P->width, &Ans_matrix_1);
            Create_Matrix( "Ans2 HxW", Ans_matrix_data_2 , P->height, P->width, &Ans_matrix_2);
            /* ------------ P = (I - LiCi)P ------------ */
            matrix_float_mul( &Li, &Ci, &Ans_matrix_1 );            /* LiCi */
            matrix_float_sub(&I_matrix, &Ans_matrix_1);             /* I - LiCi */
            matrix_float_mul(&I_matrix, P, &Ans_matrix_2);         /* (I - LiCi)P */
            matrix_float_copy( P, &Ans_matrix_2);                  /* P = (I - LiCi)P */
            /* ------------ Xhat = xhat + Li ( yi[n] - hx ) ------------ */
//            matrix_float_sub( , );
        }
    }

    return 0;
}

int Create_Matrix( char* string, float *data, int height, int width, matrix_float *Matrix ){
    data = (float *)malloc( (height*width)*sizeof(float));
    Matrix->data = data;
    Matrix->name = string;
    Matrix->height = height;
    Matrix->width = width;
    return 0;
}
