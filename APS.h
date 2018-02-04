//
// Created by Matthew Liu on 2018/02/03.
//

#ifndef MANSEDS_APS_H
#define MANSEDS_APS_H

class APS {
public:
    /// Constructor, name the Altitude Positioning System object if you so choose
    explicit APS(std::string name);

    /// Getters, Functions that lets you get data you need
    /// Get GPS data
    std::string get_GPS_data();
    double get_GPS_time();
    double get_GPS_lon();
    double get_GPS_lat();
    double get_GPS_alt();

    /// Get GLONASS data
    std::string get_GLO_data();
    double get_GLO_time();
    double get_GLO_lon();
    double get_GLO_lat();
    double get_GLO_alt();

    /// Setters, Functions that lets you input data into the function
    void GPS_data_in(std::string GPS_data);
    std::string GLO_data_in(std::string GLO_data);

private:
    /// Private variables to prevent cross contamination
    std::string _name;

    std::string _GPS_data;
    double _GPS_time;
    double _GPS_lon;
    double _GPS_lat;
    double _GPS_alt;

    std::string _GLO_data;
    double _GLO_time;
    double _GLO_lon;
    double _GLO_lat;
    double _GLO_alt;

    char _spacing = ',';
    std::string _string1;
    std::string _string2;
};

#endif //MANSEDS_APS_H
