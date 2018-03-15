/*
    main.cpp
    MANSEDS Self-Landing Rocket code
    Contributors: Alex Koch, Ethan Ramsay

    Entry point for the whole program. Manages the tasks that need to be exectuted throughout the whole process.

    Program is split up as follows:
    
    1. Initialisation (Prior to launch)
        > Initialise time
        > Initialise I2C
        > Initialise IMUs
        > Initialise GPS module
            ~ Check that the target location is within a reasonable distance of current (launch location)
        > Open/create data files
        > Initialise stacks
        > Initialise thread pool and assign threads. Need threads for: (Look into whether or not to set affinity for each thread to lock it to a certain processor)
            - Polling sensors (Throughout the flight)
            - Saving data (Throughout the flight)
            - Monitoring of the flight (Throughout flight - Tasks to be split between main thread and another spawned thread)
            - Controlling fin actuators (Upper descent)
            - Controlling fin actuators and deploying legs (Lower descent)
        > Open up wireless and Listen for launch command

    2. Launch Command
        > Recieve launch command via wireless
        > Close of wireless communication
        > Initiate launch

    3. Ascent monitoring
        > Read Sensors to stacks
        > Save to files
        > Abort monitoring
        > Motor monitoring (via acceleration)
        > Motor shutdown after time
        > Acceleration or velocity for firing the second stage

    4. Appogee detection
        > Deploy fins 

    5. Decent control
        Upper Descent
        > Read sensors
        > Save sensor data
        > Abort monitoring
        > Flight path prediction
        > Steering of rocket
        > Monitor for when and during the firing the motor to slow down descent

        Lower Descent
        > Read sensors
        > Save sensor data
        > Abort monitoring
        > Steer rocket into upright landing position and maintain oreintation
        > Motor monitoring during firing and shutdown when appropriate / Parachute deployment
        > Landing leg deployment when appropriate (monitor via altitude)

    6. Touchdown detection
        > Check for motor shutdown, ensure solenoid valve is in 'closed' position and ignitor is turned off. 
        > Wait appropriate period of time to ensure flame is extinguished 
        > Then vent oxidiser slowly
        > Restart wireless transmission
        > Check subsystems and transmit all clear or no go signal.
        
    7. Save data

    8. Terminate program

    TO DO: (BY NO MEANS A COMPLETE LIST!)
        Add your name to the google drive next to the tasks you are completing: https://docs.google.com/spreadsheets/d/18tTD7q6DT0AlY1_XBud34gNhlpI3fMTlMXtsfzcRgaI/edit?usp=sharing
        > define abort functions (different aborts depending on what part of the flight)
        > Reading GPS data
        > Logginf GPS data and finding the average position. Use a Kalman filter.
        > Reading IMU data
        > Logging IMU data and finding average acceleration and logging this. Look into cross validation with other data sources of acceleration.
        > Initialisation of I2C
        > Thread Pool
        > Custom stacks and queues (in testing phase currently)
        > Launch detection (for use when using a solid motor and to double check hybrid has worked when the hybrid motor is used)7
        > Detecting Appogee
        > Detecting when landing height has been reached. Which is about 10 m. Add this variable to global_variables.h so that it can be easily changed.
        > Detecting when the rocket has landed. 

    Notes:
        > Define functions which cause an action, i.e. deploy_fins() as bool functions which return 
          true if executed successfully and false otherwise! Allows for easier abort control and error logging.
        > Log all successful and unsuccessful actions in the log file in the format 
          log_file << current_time() << ": COMMENT" << std::endl;
        > Use easy to understand variable and function names. The rule of thumb is that the name is 
          unsuitable if you ever have to explain the name either in person or by a comment
*/

// Import necessary libraries

#include <thread> // for std::thread and other  multi-threading functions
#include <fstream> // For saving to files
#include <chrono> // For keep track of time

// Import header files, please add any relevant header files here

#include "global_variables.h"

// Initialise log and data files to be saved to

std::ofstream log_file{ "log.txt" }; 
log_file << "Time / ms       |      Log" << std::endl << std::endl;
std::ofstream acceleration_file{ "acceleration_data.txt" }
std::ofstream GPS_file{ "GPS_data.txt" }

using t_now = std::chrono::high_resolution_clock::now();
auto t_0 = t_now; // Define as a global variable
double current_time() // returns the current time in ms from the start time t_0 as a double
{
    return std::chrono::duration<double, std::milli>(t_now - t_0).count()
}

bool initialise_stacks()
// Initialises the stacks' size and catches any memory allocation faults
// Fills the stacks so that they are fully initilised (e.g. stack.size() == stack.max_size()). 
// This is to ensure that non of the elements are undefined.
{
    try
    {
        acceleration = f_ring_stack<double>{ 8 }; // Initialise stacks 
    }
    catch(/*memory allocation problem*/)
    {
        return false;
    }
    for(int i=0; i < acceleration.max_size(); i++)
    {
        read_IMUs(); 
    }
    return true;
}

/*
MULTI-THREADING CONTROL

A thread pool is initialised at the start of the program which is then assigned to run certain functions.
Some of the functions, including the sensor reading and data saving functions, run continously via a while(true) loop which is interupted 
when necessary via a terminate command issued changing a global boolean to false. Can look into using thread termination commands that are
platform specific for the raspberry pi in the future to speed things up.
Need threads for: (Look into whether or not to set affinity for each thread to lock it to a certain processor)
            - Polling sensors (Throughout the flight)
            - Saving data (Throughout the flight)
            - Monitoring of the flight (Throughout flight - Tasks to be split between main thread and another spawned thread)
            - Controlling fin actuators (Upper descent)
            - Controlling fin actuators and deploying legs (Lower descent)
Affinity: https://eli.thegreenplace.net/2016/c11-threads-affinity-and-hyperthreading/
Setting affinity is system dependent, define once final operating has been set!
*/

bool is_reading_sensors{ true }; // Global variable which can be changed in order to end the while loop within the thread
void read_sensors() // function placed within a thread to read sensor data and place them on their associated stacks
{
    log_file << current_time() << ": Began reading sensors" << std::endl;
    while(is_reading_sensors) 
    {
        read_IMUs(); 
        read_GPS();
    }
    log_file << current_time() << ": Stopped reading sensors" << std::endl;
}

bool is_saving_data{ true };
void save_data_to_file() // function placed within a thread to save sensor data to various files
{
    log_file << current_time() << ": Began saving data to files." << std::endl;
    while(is_saving_data)
    {
        // Save IMU data to file
        // Save GPS data to file
    }
    log_file << current_time() << ": Stopped saving data to files." << std::endl;
}

int main()
{
    // 1. Initialisation

    // Initialise time
    t_0 = t_now; // Reset the start time

    // Initialise I2C, IMUS and GPS
    if(initialise_I2C())
    {
        log_file << current_time() << ": Initialised I2C successfully" << std::endl;
    }
    else
    {
        log_file << current_time() << ": ERROR! I2C initialisation unsuccessful" << std::endl;
        pre_launch_abort();
    }
    if(initialise_IMUs())
    {
        log_file << current_time() << ": Initialised IMUs successfully" << std::endl;
    }
    else
    {
        log_file << current_time() << ": ERROR! I2C initialisation unsuccessful" << std::endl;
        pre_launch_abort();
    }
    if(initialise_GPS())
    {
        log_file << current_time() << ": Initialised GPS successfully" << std::endl;
    }
    else
    {
        log_file << current_time() << ": ERROR! I2C initialisation unsuccessful" << std::endl;
        pre_launch_abort();
    }

    // Create thread pool and initialise threads

    // Open data files to save telemetry data to throughout the flight
    // Do we want to read acceleration and GPS continously into files before the launch??

    // If there is a failure is previously saved data actually saved??

    // Initialise stacks and fill with data

    if(initialise_stacks())
    {
        log_file << current_time() << ": Stacks successfully initialised" << std::endl;
    }
    else
    {
        log_file << current_time() << ": ERROR! Stack initialisation unsuccessful, memory allocation exception" << std::endl;
        pre_launch_abort();
    }

    bool is_initialising{ true };
    while(is_initialising)
    {
        // Constantly read in data from sensors int stacks
        if(launch_command()){ break; }
    }

    // 2. Launch Command

    // Close wireless transmissions
    log_file << current_time() << ": Launch command recieved" << std::endl;
    fire_motor();
    

    // 3. Ascent monitoring

    bool is_ascending{ true };
    while (is_ascending)
    {   
        // Read Sensors to stacks
        // Save to files
        // Abort monitoring
        // Motor monitoring (via acceleration)
        // Motor shutdown after time
        // Acceleration or velocity for firing the second stage
        if(appogee()){ break; } // 4. Appogee detection & 
    }

    // deployment of fins etc.
    deploy_fins();

    // 5. Decent control & Monitoring
    bool is_upper_descent{ true };
    while(is_upper_descent)
    {
        // Read sensors
        // Save sensor data
        // Abort monitoring
        // Flight path prediction
        // Steering of rocket
        // Monitor for when and during the firing the motor to slow down descent
        if(cut_off_altitude()){ break; } // Rocket is now at the altude to start land
    }
    bool is_landing{ true };
    while(is_landing)
    {   
        // Read sensors
        // Save sensor data
        // Abort monitoring
        // Steer rocket into upright landing position
        // Motor monitoring during firing and shutdown when appropriate
        if(landed()){ break; } // 6. Touchdown detection
    }
    // 7. Save data to files

    // 8. Terminate program

    return 0;
}
