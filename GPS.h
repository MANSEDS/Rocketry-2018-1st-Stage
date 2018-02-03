//
// Created by Matthew Liu on 2018/01/26.
//

#ifndef MANSEDS_GPS_H
#define MANSEDS_GPS_H

#include <iostream>
#include <list>
#include "GPS.h"

class GPS {
public:
    explicit GPS(std::string name);
    void add_data(int data);
    void add_time(int time);
    void add_lon(int lon);
    void add_lat(int lat);

    /// Getters, Functions that lets you get data you need
    std::string GPS_Call() {
        return _data;
    }
    std::string Get_Time() {
        return _time;
    }

    std::string Get_Long() {
        return _long;
    }

    std::string Get_Lati() {
        return _lati;
    }

    /// Setters, Functions that lets you input data into the function
    std::string data_in(std::string stuff) {
        _data = stuff;
    }

private:
    std::string _name;
    std::string _data;
    std::string _time;
    std::string _long;
    std::string _lati;
};

#endif //MANSEDS_GPS_H
