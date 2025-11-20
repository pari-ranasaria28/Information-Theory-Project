/**
  Cross-platform CTimer (Windows + Linux + macOS)
  Patched for Intel oneAPI on Windows
*/

#ifndef CLASS_CTimer
#define CLASS_CTimer

#define USE_CUSTOM_TIMER

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

#ifdef _WIN32
    // Windows high-resolution timer
    #include <windows.h>
#else
    // Linux / macOS
    #include <time.h>
    #include <sys/time.h>
    #include <stdlib.h>

    #ifdef __MACH__
        #include <mach/clock.h>
        #include <mach/mach.h>
    #endif
#endif

class CTimer
{
private:

#ifdef _WIN32
    LARGE_INTEGER freq;
    LARGE_INTEGER t_start;
    LARGE_INTEGER t_stop;
#else
    timespec t_start;
    timespec t_stop;
#endif

    bool isRunning;

protected:

#ifndef _WIN32
    long diff_ns(timespec start, timespec end);
    long diff_sec(timespec start, timespec end);
#endif

public:
    CTimer(bool _start);
    CTimer();

    void start();
    void stop();
    void reset();

    long get_time_ns();
    long get_time_us();
    long get_time_ms();
    long get_time_sec();
};

#endif
