//
// Created by Matthew Liu on 2018/02/14.
//

#include "Rocket_Library.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>


/// Library for Cartesian vectors
cartesian_vector::cartesian_vector(CartV your_vector) {
        _vector = your_vector;
}

    /// Setters for Cartesian vectors
    void cartesian_vector::set_x(double x) {
        _vector.x = x;
    }
    void cartesian_vector::set_y(double y) {
        _vector.y = y;
    }
    void cartesian_vector::set_z(double z) {
        _vector.z = z;
    }

    /// Getters for Cartesian vectors
    double cartesian_vector::magnitude() {
        double magnitude = sqrt( pow(_vector.x,2) + pow(_vector.y,2) + pow(_vector.z,2) );
        return magnitude;
    }
    double cartesian_vector::x_hat() {
        return _vector.x;
    }
    double cartesian_vector::y_hat() {
        return  _vector.y;
    }
    double cartesian_vector::z_hat() {
        return  _vector.z;
    }

    /// Operations for Cartesian vectors
    double cartesian_vector::dot_product(CartV another_vector) {
        return ( _vector.x * another_vector.x + _vector.y * another_vector.y + _vector.z * another_vector.z);
    }
    CartV cartesian_vector::addition(CartV another_vector) {
        CartV output_vector;
        output_vector.x = _vector.x + another_vector.x;
        output_vector.y = _vector.y + another_vector.y;
        output_vector.z = _vector.z + another_vector.z;
        return output_vector;
    }
    CartV cartesian_vector::subtraction(CartV another_vector) {
        CartV output_vector;
        output_vector.x = _vector.x - another_vector.x;
        output_vector.y = _vector.y - another_vector.y;
        output_vector.z = _vector.z - another_vector.z;
        return output_vector;
    }