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
                _num = 0;
            }
            else if (_string1 == "S") {
                _num = 1;
            }
            switch (_num) {
                case 0:
                    _GPS_lon = stod(_string2);
                case 1:
                    _GPS_lon = -1 * stod(_string2);
                default:
                    _GPS_lon = 0;
            }
        }

        else if (x == 5) {
            _string2 = _string1;
        }

        else if (x == 6) {
            if (_string1 == "E") {
                _num = 0;
            }
            else if (_string1 == "W") {
                _num = 1;
            }
            switch (_num) {
                case 0:
                    _GPS_lat = stod(_string2);
                case 1:
                    _GPS_lat = -1 * stod(_string2);
                default:
                    _GPS_lat = 0;
            }
        }
        x++;
    }
}


std::string APS::GLO_data_in(std::string GLO_data) {
    _GLO_data = GLO_data;
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

/// Get GLONASS data
std::string APS::get_GLO_data() {
    return _GPS_data;
}
double APS::get_GLO_time() {
    return _GPS_time;
}

double APS::get_GLO_lon() {
    return _GPS_lon;
}

double APS::get_GLO_lat() {
    return _GPS_lat;
}