#ifndef TIME_H
#define TIME_H
/******************************************************************************

    source file Time.h for class: Time

    Used to share _time inside the simulator

    Author : Bingjie FU
    Version: 1
    Date   : April 2005

******************************************************************************/
#include "TraceManager.h"

class Time
{
    // Constanst(s)

    // Variable(s)
    private:
    double time;


    // Function(s) declarations
    public:

//------------------------------------------------------------------------------
//  Time()
//------------------------------------------------------------------------------
    Time()
    {
        time = 0.0;
    }

//------------------------------------------------------------------------------
//  ~Time()
//------------------------------------------------------------------------------
    //~Time();

//------------------------------------------------------------------------------
//  double getTime()
//
//  return the _time
//------------------------------------------------------------------------------

    double getTime() const
    {
        return time;
    }

//------------------------------------------------------------------------------
//  void setTime(double t)
//
//  set the _time
//------------------------------------------------------------------------------

    void setTime(const double &time)
    {
        TRACE("Time::setTime-->");
        this->time = time;
        //PRINTLN("_time" << time);
        TRACE("Time::setTime<--");
    }

//------------------------------------------------------------------------------
//  void resetTime()
//
//  reset the _time
//------------------------------------------------------------------------------
    void reset()
    {
        TRACE("Time::reset-->");
        time = 0.0;
        //PRINTLN("_time" << time);
        TRACE("Time::reset<--");
    }

}; // end of declarations
#endif //TIME_H
