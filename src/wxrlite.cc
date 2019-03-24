#include "wxrlite.h"

#include <bcm2835.h>  // communicate with gpio
#include <stdint.h>   // fixed width ints to hold Pixel values
#include <unistd.h>   // usleep
#include <stdlib.h>   // basically everything I think
#include "pixel.h"    // Pixel and PixelList classes
#include "clinkt.h"   // just leave this one in
#include <iostream>   // genuinely only here to output the word 'Dead'

#include <math.h>     // round


//! (Not Used) 
void GetWXRdata::init() {}

//! Requests real-time Seattle weather data from openweathermap.org,
//! stores that data in a json object and pulls wind speed and wind
//! direction from it and sends those values to the ledwind() method.
void GetWXRdata::start() {
    
    Client c;
        //      Server URL                            ID for Seattle  Imperial = non-metric units   Appid = API Key (this key will not work, you need your own!)
        c.get("https://api.openweathermap.org/data/2.5/weather?id=5809844&units=imperial&appid=dfd263074cf6ada7f07b057a79b24853", [this](json& response){
            //std::cout<<response.dump(4)<<std::endl;
            _data = response;
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        c.process_responses();

        //std::cout<<_data.dump(4)<<std::endl;                              // displays recieved json data
        _wspeed = _data["wind"]["speed"];                                   //Imperial = miles/hour (mph)
        //std::cout << "Wind Speed: " << _wspeed << " mph" << std::endl;    // check string to double
        _wspeed /= 1.151;                                                   // converts mph to knots
        //std::cout << "Wind Speed: " << _wspeed << " knots" << std::endl;  // check conversion
        _wspeed = round(_wspeed);                                           // rounds to the nearest knot
        _wdeg = _data["wind"]["deg"];                                       // degrees (deg)
        std::cout << "Wind Speed: " << _wspeed << " knots" << std::endl;
        std::cout << "Wind Direction: " << _wdeg << " deg" << std::endl << std::endl;
    
    GetWXRdata::ledwind(_wspeed, _wdeg);
}

//! Requests real-time Seattle weather data from openweathermap.org,
//! stores that data in a json object and pulls wind speed and wind
//! direction from it and sends those values to the ledwind() method.
void GetWXRdata::update() {
    Client c;
        //      Server URL                            ID for Seattle  Imperial = non-metric units   Appid = API Key (this key will not work, you need your own!)
        c.get("https://api.openweathermap.org/data/2.5/weather?id=5809844&units=imperial&appid=dfd263074cf6ada7f07b057a79b24853", [this](json& response){
            //std::cout<<response.dump(4)<<std::endl;
            _data = response;
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
        c.process_responses();
        
        //std::cout<<_data.dump(4)<<std::endl;
        _wspeed = _data["wind"]["speed"]; //Imperial = miles/hour (mph)
        //std::cout << "Wind Speed: " << _wspeed << " mph" << std::endl;
        _wspeed /= 1.151; // converts mph to knots
        //std::cout << "Wind Speed: " << _wspeed << " knots" << std::endl;
        _wspeed = round(_wspeed); // rounding
        _wdeg = _data["wind"]["deg"]; // degrees (deg)
        std::cout << "Wind Speed: " << _wspeed << " knots" << std::endl;
        std::cout << "Wind Direction: " << _wdeg << " deg" << std::endl << std::endl;
        
        GetWXRdata::ledwind(_wspeed, _wdeg);
}

//! Turns off the LEDs on the RPi and nicely stops the gpio bus.
void GetWXRdata::stop() {
    int dummy = 0;
    dieNicely(dummy); // darkens pixels and stops gpio nicely
}

//! Sends wind information to RPi for LED display.
    /*! 
      \param windspeed The wind speed in knots
      \param winddeg The wind direction in degrees
      \return int 0 = normal op, int 1 = unsuccessful op
    */
int GetWXRdata::ledwind(double windspeed, double winddeg) {
    int kpp = 2;    // knots per pixel

    if (clinkt_start()){
        std::cout << "Unable to start apa102: bcm not initialising?\n";
        return 1;
    }

    signal(SIGINT, dieNicely);   // On keyboard interrupt, darkens pixels and stops gpio
                                 // uses exit(0) - write your own if that is a deal-breaker

    PixelList PL(NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) {
        PL.setP(3, i);
    }

    // color definitions for cardinal headings
    uint32_t Gray    = 0x069696901; // N  (338 -  23)
    uint32_t Blue    = 0x00000ff01; // NE ( 23 -  68)
    uint32_t Lime    = 0x000ff0001; // E  ( 68 - 113)
    uint32_t Cyan    = 0x000ffff01; // SE (113 - 158)
    uint32_t Red     = 0x0ff000001; // S  (158 - 203)
    uint32_t Magenta = 0x0ff00ff01; // SW (203 - 248)
    uint32_t Yellow  = 0x0ffff0001; // W  (248 - 293)
    uint32_t White   = 0x0ffffff01; // NW (293 - 338)

    //while (true) {
            
        // sets # of LEDs based on wind magnitude
        // sets color of LEDs based on wind direction
        int i = 0;
        for(i = 0; i < (windspeed / kpp) - 1; i++) {
            // check for i > # of LEDs
            if( (windspeed / kpp -1) > NUM_LEDS ) {
                i = NUM_LEDS;
            }

            if(winddeg >= 338 && winddeg < 360 || winddeg >= 0 && winddeg < 23) {
                PL.setP(Gray, i);
            }
            if(winddeg >= 23 && winddeg < 68) {
                PL.setP(Blue, i);
            }
            if(winddeg >= 68 && winddeg < 113) {
                PL.setP(Lime, i);
            }
            if(winddeg >= 113 && winddeg < 158) {
                PL.setP(Cyan, i);
            }
            if(winddeg >= 158 && winddeg < 203) {
                PL.setP(Red, i);
            }
            if(winddeg >= 203 && winddeg < 248) {
                PL.setP(Magenta, i);
            }
            if(winddeg >= 248 && winddeg < 293) {
                PL.setP(Yellow, i);
            }
            if(winddeg >= 293 && winddeg < 338) {
                PL.setP(White, i);
            }
            
            PL.show();
            usleep(100000);
        }
        
        usleep(100000);

    return 0;
}