/// Inertial Measurement Unit Data Class

/// Authors : Ethan Ramsay, Alex Koch
/// Created : 3/2/2017

/*

A data class for the collection and storage of IMU data.
Part of the MANSEDS Rocketry Project.

*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"

struct IMU_data {
    int IMU_identity;
    int16_t[3] acc;
    int16_t[3] ang_vel;

    IMU_data()
    {
        IMU_identity = '0';
        acc = {0, 0, 0};
        ang_vel = {0, 0, 0};
    }

    IMU_data(int identity_, int16_t acc_, int16_t ang_vel_)
    {
        IMU_identity = identity_;
        acc = acc_;
        ang_vel = ang_vel_;
    }
    IMU_data(int identity_, int16_t ax, int16_t ay, int16_t az, int16_t  gx, int16_t gy, int16_t gz)
    {
        IMU_identity = identity_;
        acc[0] = ax;
        acc[1] = ay;
        acc[2] = az;
        ang_vel[0] = gx;
        ang_vel[1] = gy;
        ang_vel[2] = gz;
    }
}

// example
IMU_data motionData; // initialised a struct called 'motionData' of type IMU_data with zeros

std::stack<IMU_data> raw_IMU_stack

/// Initialise class name
IMU::IMU(int identity) {
    _name = name;
}

/// Collect acceleration and angular rotation data from IMU
void IMU::IMU_data_collection(int IMU_identity, MPU6050[] IMUs) {
    int16_t[3] acc, ang_vel;
    IMUs[IMU_identity].getMotion6(&D.acc[0], &D.acc[1], &D.acc[2], &D.ang_vel[0], &D.ang_vel[1], &D.ang_vel[2]);
}

/// Collect angular rotation data only from IMU
void IMU::IMU_data_collection(int IMU_identity, MPU6050[] IMUs) {
    int16_t[3] acc, ang_vel;
    IMUs[IMU_identity].getRotation(&D.acc[0], &D.acc[1], &D.acc[2], &D.ang_vel[0], &D.ang_vel[1], &D.ang_vel[2]);
}

/// Collect acceleration data only from IMU
void IMU::IMU_data_collection(int IMU_identity, MPU6050[] IMUs) {
    int16_t[3] acc;
    IMUs[IMU_identity].getAcceleration(&D.acc[0], &D.acc[1], &D.acc[2]);
}
