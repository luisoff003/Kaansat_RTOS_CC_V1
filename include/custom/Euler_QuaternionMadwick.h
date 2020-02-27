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
 * Euler_QuaternionMadwick.h
 *
 *  Created on: 26/02/2020
 *      Author: Luison
 */

#ifndef INCLUDE_CUSTOM_EULER_QUATERNIONMADWICK_H_
#define INCLUDE_CUSTOM_EULER_QUATERNIONMADWICK_H_

float twoKp;        // 2 * proportional gain (Kp)
float twoKi;        // 2 * integral gain (Ki)
float q0, q1, q2, q3;   // quaternion of sensor frame relative to auxiliary frame
float integralFBx, integralFBy, integralFBz;  // integral error terms scaled by Ki
float invSampleFreq;
float roll, pitch, yaw;
char anglesComputed;

void Mahony(void);
static float invSqrt(float x);
void computeAngles();
void begin(float sampleFrequency);
void update(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void updateIMU(float gx, float gy, float gz, float ax, float ay, float az);
float getRoll(void);
float getPitch(void);
float getYaw(void);
float getRollRadians(void);
float getPitchRadians(void);
float getYawRadians(void);


#endif /* INCLUDE_CUSTOM_EULER_QUATERNIONMADWICK_H_ */
