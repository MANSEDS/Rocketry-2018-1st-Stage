//
// Created by Matthew Liu on 2018/02/14.
//

#ifndef MANSEDS_ROCKET_LIBRARY_H
#define MANSEDS_ROCKET_LIBRARY_H

#include <iostream>

/// All global constants
const double pi = 3.141592653589793;
const std::string IMU_port[3] = { "port1" , "port2" , "port3" };

class cartesian_vector {
public:

    /// Structue of a cartesian vector
    struct CartV{ double x; double y; double z; };

    /// Constructor, initialize with corrisponding vector
    explicit cartesian_vector(CartV your_vector);

    /// Operations avalible for the class
    /// Vector Operations
    double dot_product(CartV another_vector);
    CartV addition(CartV another_vector);
    CartV subtraction(CartV another_vector);
    /// Getters
    double magnitude();
    double x_hat();
    double y_hat();
    double z_hat();
    /// Setters
    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

private:
    CartV _vector;
};

class polar_vector {
public:

    /// Structue of a plane polar vector
    struct PolaV{ double r; double theta; double z; };

    /// Constructor, initialize with corrisponding vector
    explicit polar_vector(PolaV your_vector);

    /// Operations avalible for the class
    /// Vector Operations
    PolaV dot_product(PolaV another_vector);
    PolaV addition(PolaV another_vector);
    PolaV subtraction(PolaV another_vector);
    /// Getters
    double magnitude();
    double r_hat();
    double theta_hat();
    double z_hat();
    /// setters
    void set_r(double r);
    void set_theta(double theta);
    void set_z(double z);

private:
    PolaV _vector;
};


#endif //MANSEDS_ROCKET_LIBRARY_H
