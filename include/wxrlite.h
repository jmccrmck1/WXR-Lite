#ifndef WXRLITE_H
#define WXRLITE_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "elma.h"

using namespace elma;

//! A process that obtains json weather data using an HTTP client, 
//! extracts wind data values and sends to RPi LED output.
class GetWXRdata : public Process {

    public:
    //! Constructor      
    GetWXRdata() : Process("Get_WXR_Data") {}

    //! Initialization method. (not called in this project)
    void init();

    //! Start method.
    void start();

    //! Update method.
    void update();

    //! Stop method.
    void stop();

    // documentation for this method is in wxrlite.cc
    int ledwind(double windspeed, double winddeg);

    private:
    // Instance Variables
    json _data;
    double _wspeed,
           _wdeg;
};

#endif