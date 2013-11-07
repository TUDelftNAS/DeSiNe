#ifndef TRACEMANAGER_H
#define TRACEMANAGER_H
/******************************************************************************

    header file TraceManager.h for class: TraceManager

    This class is responsible for handling the traces used fot debugging. It
    also offers some convenience functions/macro's for sending output to the
    screen. It uses some global variables because of the macro's.

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/


// Include(s)
#include <iostream>
using std::cerr;
using std::cout;
using std::flush;
using std::endl;
using std::ostream;
using std::streambuf;


class TraceManager
{
    // Constanst(s)
    public:
    const static unsigned short precision;

    // Variable(s)
    public:
    static ostream* trace_out;

    private:
    static TraceManager* the_instance;

    // Function(s) declarations
    private:
//------------------------------------------------------------------------------
//
//  constructor TraceManager();
//
//  Constructs TraceManager. Must use intialize().
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    TraceManager();


    public:
//------------------------------------------------------------------------------
//
//  static void intialize();
//
//  Initialized this object (singleton) without starting the tracing!!
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    static void initialize();


//------------------------------------------------------------------------------
//
//  ostream* getStream()
//
//  Returns the ostream
//
//------------------------------------------------------------------------------
    static ostream* getStream()
    {
        return trace_out;
    }


//------------------------------------------------------------------------------
//
//  void start();
//
//  Starts tracing
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    static void start()
    {
        trace_out->rdbuf(cout.rdbuf());
    }

//------------------------------------------------------------------------------
//
//  void stop();
//
//  Stops tracing
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    static void stop()
    {
        trace_out->rdbuf((streambuf*) 0);
    }


}; //end declarations Streamer


// define trace macro
//#define NO_TRACES
#ifndef NO_TRACES
    #define TRACE(x) \
    *TraceManager::trace_out << x << endl;
#else  //TRACES
    #define TRACE(x)
#endif //TRACES

//#define NO_DEBUGS
#ifndef NO_DEBUGS
    #define DEBUG(x) \
    cerr << x << endl;
#else  //DEBUG
    #define DEBUG(x)
#endif //NO_DEBUGS

// define error macro
#define ERROR(x) \
    cerr << "ERROR: " << x << endl;

// define warning macro
#define WARNING(x) \
    cerr << "WARNING: " << x << endl;

// define print macro, convenience function
#define PRINT(x) \
    cout << x;

#define PRINTLN(x) \
    PRINT(x << endl)

#endif //TRACEMANAGER_H
