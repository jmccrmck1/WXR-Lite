#ifndef WXRLITE_H
#define WXRLITE_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "elma.h"

using namespace elma;


class GetWXRdata : public Process {

    public:
    GetWXRdata() : Process("Get_WXR_Data") {}

    void init();
    void start();
    void update();
    void stop();

    int ledwind(double windspeed, double winddeg);

    private:
    json _data;
    //double _wspeed = 0;
    //double _wdeg = 0;
    double _wspeed,
           _wdeg;
};

#endif