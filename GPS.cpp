//
// Created by Matthew Liu on 2018/01/26.
//

#include "GPS.h"

GPS::GPS(std::string name) {
    _name = name;
}

void GPS::add_data(int data) {
    _data = data;
}

void GPS::add_time(int time) {
    _time = time;
}

void GPS::add_lon(int lon) {
    _long = lon;
}

void GPS::add_lat(int lat) {
    _lati = lat;
}

