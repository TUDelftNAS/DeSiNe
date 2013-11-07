#ifndef TIMER_H
#define TIMER_H
/******************************************************************************

    header file Timer.h for utility class Timer.

    This is a class for timing an interval between two calls in msec

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2004

******************************************************************************/


// Include(s)
#include <ctime>
using std::clock;
using std::clock_t;

class Timer
{
    // Constanst(s)

    // Variable(s)
    private:
    clock_t the_time;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor Timer()
//  Constructs empty Timer.
//  Input :
//  Output:
//------------------------------------------------------------------------------
//    Timer() {}


//------------------------------------------------------------------------------
//  destructor ~Timer()
//  Destructs Timer
//  Input :
//  Output:
//------------------------------------------------------------------------------
//    ~Timer() {}


//------------------------------------------------------------------------------
// void start()
//
// Starts the timer
//
//------------------------------------------------------------------------------
    void start()
    {
#ifndef NO_TIMER
        the_time = clock();
#endif // NO_TIMER
    }


//------------------------------------------------------------------------------
// float read()
//
// Reads the time ibterval since the last start()
//
//------------------------------------------------------------------------------
    float read()
    {
#ifndef NO_TIMER
        double result = (double) (clock() - the_time) / CLOCKS_PER_SEC;
        return (float) (1000.0*result);
#else  // NO_TIMER
        return 0.0;
#endif // NO_TIMER
    }
}; //end declarations Timer
#endif // TIMER_H
