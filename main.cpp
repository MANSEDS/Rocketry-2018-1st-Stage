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

/// Read in data in NMEA format, Time in GMT "123456.123,A" Longitude "123456.1234,N"   Latitude "123456.1234,W"
/// Quality "1"   # of satalites "09"   HDOP "1.6"   Altitude "7000.6"
/// std::string GPS_Data = "$GPRMC,123456.123,A,123456.1234,N,123456.1234,W,1,09,1.6,7000.6,M,-20.7,M,234,10000*20

std::ofstream GPS_Data;
GPS_Data.open ("GPS_Data.txt");
GPS GPS1("GPS1");
std::string GPS_data = "Stream GPS data into here";

int x = 0;
int readcount = 100;

/// loop data calling Proto-call
while (x <= readcount) {

    /// add time delay, operating environment specific

    /// stream gps data into the gps object
    GPS1.data_in(GPS_data);
    /// redundant step, to show how to call gps data
    std::string data = GPS1.GPS_Call();
    /// seperate each line with ;
    GPS_Data << data + ";";
    x +=1;
}

/// End data updates
GPS_Data.close();


/// IMU Data Acquisition
/// Ethan 


/// Kalman Filtering
/// Ben 
/// Output filter_data object 

/// Difference function
/// 

/// PID Control
/// 

/// Actuator Control
/// Ethan

return 0
