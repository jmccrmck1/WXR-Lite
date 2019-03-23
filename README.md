WXR-Lite
===

[WXR-Lite](https://github.com/jmccrmck1/WXR-Lite) is an example embedded systems project that demonstrates using the event loop and process manager libray "Elma" on a Raspberry Pi to pull weather data from a website to manipulate LEDs.

The source code for this project is available [on github](https://github.com/jmccrmck1/WXR-Lite).

Project Goals
===

What will I do?
The objective of this project is to use Elma on a raspberry pi along with http.h and json.h to obtain local Seattle weather and then create a visual response that correlates to the data being received.  I am leaning on using wind speed and direction to control LED intensity and color spectrum.  The idea being the creation of an informative visual que of local wind conditions.

What will it mean for me to succeed?
Not having used a raspberry pi before sucess will be getting any portion of this functionality to work.  That being said I really want to be able to succeed at obtaining online data and responding to it in some meaningful fashion using the Elma library.

What resources will I use?
As mentioned previously this project will use a raspberry pi along with LED sensors of some kind.  An online weather data source such as NOAA, Google, etc. will also be used.

Milestones
===

1. Get Docker, Doxygen, Google Test, Visual Studio Code and Elma working on Raspberry Pi - 3/17/19
2. Include http.h and json.h library - 3/17/19
3. Get weather related data from on-line source - 3/19/19
4. Develop process that responsds to weather data - 3/21/19
5. Completing API documentation for project - 3/22/19

Accomplishments to Date:
===

Installed Raspian, Docker and Visual Studio on Raspberry Pi.
Confirmed Doxygen, Google Test, and Elma work on Raspberry Pi via Docker.

Installation
---

    git clone https://github.com/klavinslab/elma_project.git
    cd elma_project
    docker run -v $PWD:/source -it klavins/elma:latest bash
    make
    make docs


Execution
---
To run the stopwatch, type

    bin/stopwatch

The stopwatch is controlled via the keyboard, via these keys:
- **s**: Start or stop
- **l**: Lap
- **r**: Reset
- **q**: Quit

Testing
---
To run tests, do
```bash
bin/test
```

Architecture
---
Describe how your project was designed, what choices you made, how things are organized, etc.

Results
---
Describe the results of testing and running your code. Include visuals when possible.

Acknowledgements
---
Mention anyone who helped you and how.

References
---
List all libraries, articles, stack overflow answers, etc. that you used to get your code working.
"# WXR-Lite" 
