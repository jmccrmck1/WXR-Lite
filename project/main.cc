#include "elma.h"
#include "wxrlite.h"
#include <iostream>
#include <ratio>

using namespace std::chrono;

//#define S(__s__) high_resolution_clock::duration(seconds(__s__))
#define MIN(__min__) high_resolution_clock::duration(minutes(__min__))

int main(){
    elma::Manager m;
    GetWXRdata Data1;
    m.schedule(Data1, MIN(5))
     .start()
     .run(MIN(60));
}



/*
#include <stdio.h>
#include <iostream>
#include <string>
//#include <chrono>
//#include <vector>

#include "elma.h"

//using namespace std::chrono;
using namespace elma;

//#include "gtest/gtest.h"

int main(int argc, char **argv) {

  class GetWXRdata : public Process {

    public:
    GetWXRdata() : Process("Get_WXR_Data") {}

    void init();
    void start();
    void update();
    void stop();

    private:
    json _data;
  };

  void GetWXRdata::init() {}

  void GetWXRdata::start() {}

  void GetWXRdata::update() {
    Client c;

      c.get("https://api.openweathermap.org/data/2.5/weather?id=5809844&units=imperial&appid=dfd263074cf6ada7f07b057a79b24853", [this](json& response){
        std::cout<<response.dump(4)<<std::endl;
        _data = this.response;
      });
      std::this_thread::sleep_for(std::chrono::seconds(1));
      c.process_responses();

      double windspeed = _data["wind"]["speed"]; //Imperial = miles/hour (mph)
      windspeed /= 1.151; // converts mph to knots
      double winddeg = _data["wind"]["deg"]; // degrees (deg)
      std::cout << "Wind Speed: " << windspeed << "knots" << std::endl;
      std::cout << "Wind Direction: " << winddeg << "deg" << std::endl;
  }

  void GetWXRdata::stop() {}
}
*/
/*
  int main(int argc, char **argv) {
    
    Client c;

      c.get("https://api.openweathermap.org/data/2.5/weather?id=5809844&units=imperial&appid=dfd263074cf6ada7f07b057a79b24853", [](json& response){  
        std::cout<<response.dump(4)<<std::endl;
      });
      std::this_thread::sleep_for(std::chrono::seconds(1));
      c.process_responses();
    
      double windspeed = response["wind"]["speed"]; //Imperial = miles/hour (mph)
      windspeed /= 1.151; // converts mph to knots
      double winddeg = response["wind"]["deg"]; // degrees (deg)
      std::cout << "Wind Speed: " << windspeed << "knots" << std::endl;
      std::cout << "Wind Direction: " << winddeg << "deg" << std::endl;
  }


*/
/*
#include <bcm2835.h>  // communicate with gpio
#include <stdint.h>   // fixed width ints to hold Pixel values
#include <unistd.h>   // usleep
#include <stdlib.h>   // basically everything I think
#include "pixel.h"    // Pixel and PixelList classes
#include "clinkt.h"   // just leave this one in
#include <iostream>   // genuinely only here to output the word 'Dead'


#ifndef TEST

int main(){
  
  if (clinkt_start()){
    std::cout << "Unable to start apa102: bcm not initialising?\n";
    return 1;
  }

  signal(SIGINT, dieNicely);   // On keyboard interrupt, darkens pixels and stops gpio
                               // uses exit(0) - write your own if that is a deal-breaker

  PixelList PL(NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++)
    { PL.setP(3, i);}

  int kpp = 3;    // knots per pixel
  double windspeed = 21.6; 
  double winddeg = 0.0;

  // color definitions for cardinal headings
  uint32_t Gray    = 0x069696901; // N  (338 -  23)
  uint32_t Blue    = 0x00000ff01; // NE ( 23 -  68)
  uint32_t Lime    = 0x000ff0001; // E  ( 68 - 113)
  uint32_t Cyan    = 0x000ffff01; // SE (113 - 158)
  uint32_t Red     = 0x0ff000001; // S  (158 - 203)
  uint32_t Magenta = 0x0ff00ff01; // SW (203 - 248)
  uint32_t Yellow  = 0x0ffff0001; // W  (248 - 293)
  uint32_t White   = 0x0ffffff01; // NW (293 - 338)

  while (true) {
    
      // poll something interesting or check an interrupt
    
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
  }

  clinkt_stop(); // ends gpio nicely in the highly strange event of us getting here
  
  return 0;	
}
#endif
*/