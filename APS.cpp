//
// Created by Matthew Liu on 2018/02/03.
//

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "APS.h"

/// Initialize name for the object
APS::APS(std::string name) {
    _name = name;
}

/// Input GPS/GLONASS data
void APS::GPS_data_in(std::string GPS_data) {
    _GPS_data = GPS_data;
    int x = 0;
    std::stringstream ss(GPS_data);
    while(getline(ss,_string1,_spacing)) {
        if (x == 1) {
            _GPS_time = stod(_string1);
        }

        else if (x == 3) {
            _string2 = _string1;
        }

        else if (x == 4) {
            if (_string1 == "N") {
                _GPS_lon = stod(_string2);
            }
            else if (_string1 == "S") {
                _GPS_lon = -1 * stod(_string2);
            }
        }

        else if (x == 5) {
            _string2 = _string1;
        }

        else if (x == 6) {
            if (_string1 == "E") {
                _GPS_lat = stod(_string2);
            }
            else if (_string1 == "W") {
                _GPS_lat = -1 * stod(_string2);
            }
        }
        else if (x == 10) {
            _GPS_alt = stod(_string1);
        }
        x++;
    }
}


std::string APS::GLO_data_in(std::string GLO_data) {
    _GLO_data = GLO_data;
    int x = 0;
    std::stringstream ss(GLO_data);
    while(getline(ss,_string1,_spacing)) {
        if (x == 1) {
            _GLO_time = stod(_string1);
        }

        else if (x == 3) {
            _string2 = _string1;
        }

        else if (x == 4) {
            if (_string1 == "N") {
                _GLO_lon = stod(_string2);
            }
            else if (_string1 == "S") {
                _GLO_lon = -1 * stod(_string2);
            }
        }

        else if (x == 5) {
            _string2 = _string1;
        }

        else if (x == 6) {
            if (_string1 == "E") {
                _GLO_lat = stod(_string2);
            }
            else if (_string1 == "W") {
                _GLO_lat = -1 * stod(_string2);
            }
        }
        else if (x == 10) {
            _GLO_alt = stod(_string1);
        }
        x++;
    }
}

/// Get GPS data
std::string APS::get_GPS_data() {
    return _GPS_data;
}

double APS::get_GPS_time() {
    return _GPS_time;
}

double APS::get_GPS_lon() {
    return _GPS_lon;
}

double APS::get_GPS_lat() {
    return _GPS_lat;
}

double APS::get_GPS_alt() {
    return _GPS_alt;
}

/// Get GLONASS data
std::string APS::get_GLO_data() {
    return _GLO_data;
}
double APS::get_GLO_time() {
    return _GLO_time;
}

double APS::get_GLO_lon() {
    return _GLO_lon;
}

double APS::get_GLO_lat() {
    return _GLO_lat;
}

double APS::get_GLO_alt() {
    return _GLO_alt;
}
