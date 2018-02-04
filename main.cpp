/// Main Class for 1st Stage Rocket Control Systems - MANSEDS Rocketry 
/// 
/// Author: Ethan Ramsay, Matthew Liu

/*

*/

/// Global Variables
string target_location = "";




/// GPS & GLONASS Data Acquisition
/// Matthew

/// A program that reads in GPS Data and pushes out a textfile in CSV.
/// Connect GPS Reciever Transmittion Pin(TX) to Micro-Controller Receiver Pin(RX)

//// Read in data in NMEA format, Time in GMT "123456.123,A" Longitude "123456.1234,N"   Latitude "123456.1234,W"
/// Quality "1"   # of satalites "09"   HDOP "1.6"   Altitude "7000.6"
/// std::string GPS_Data = "$GPRMC,123456.123,A,123456.1234,N,123456.1234,W,1,09,1.6,7000.6,M,-20.7,M,234,10000*20


/// Example code for pulling data
int main() {
    APS APS1("GPS");
    std::string GPS_data = "$GPRMC,123456.123,A,123456.1234,N,123456.1234,W,1,09,1.6,7000.6,M,-20.7,M,234,10000*20";
    APS1.GPS_data_in(GPS_data);
    double output1 = APS1.get_GPS_time();
    printf("%.4f\n", output1);
    double output2 = APS1.get_GPS_lat();
    printf("%.4f\n", output2);
    double output3 = APS1.get_GPS_lon();
    printf("%.4f\n", output3);
    double output4 = APS1.get_GPS_alt();
    printf("%.4f\n", output4);
    return 0;
}


/// a function that calculates distance between two points on a sphere
double distance(double lat1, double lon1, double lat2, double lon2) {
    /// constants for calculations
    const int earth_radius = 6371000;
    double d = 2 * earth_radius * asin(sqrt(pow(sin((lat2-lat1)/2),2)+cos(lat1)*cos(lat2)*pow(sin((lon2-lon1)/2),2)));
    return d;
}

/// Outputs GPS & GLONASS objects


/// IMU Data Acquisition
/// Ethan 
/// Outputs IMU objects


/// Kalman Filtering
/// Ben 
/// Inputs IMU & GPS/GLONASS data
/// Output filter_data object 

/// Difference function
/// Oscar
/// Input location data (initially GPS & GLONASS, eventually filtered_data), target location
/// Output PI_error object 

/// PID Control
/// 
/// Input PI_error object

/// Actuator Control
/// Ethan

return 0
