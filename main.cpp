/*
    main.cpp
    MANSEDS Self-Landing Rocket code
    Contributors: Alex Koch, Ethan Ramsay

    Entry point for the whole program. Manages the tasks that need to be exectuted throughout the whole process.

    Program is split up as follows:
    
    1. Initialisation (Prior to launch)
        > Initialise I2C
        > Initialise IMUs
        > Initialise GPS module
        > Open/create data files
        > Initialise stacks
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
*/

// Import header files and necessary libraries

# include <thread>



bool initialise_stacks()
{
    
}



int main()
{
    // 1. Initialisation

    // Initialise IMUS and GPS
    initialise_I2C();
    initialise_IMUS();
    initialise_GPS();

    // Open data files to save telemetry data to throughout the flight

    // If there is a failure is previously saved data actually saved??

    // Initialise stack and fill with data

    bool is_initialising{ true };
    while(is_initialising)
    {
        // Constantly read in data from sensors int stacks
        if(launch_command()){ break; }
    }

    // 2. Launch Command

    // Close wireless transmissions
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
