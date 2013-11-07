/******************************************************************************

    source file TraceManager.cpp for class: TraceManager

    Author : T. Kleiberg
    Version: 1
    Date   : Oct 2004

******************************************************************************/



// Include(s)
#include "Utils/TraceManager.h"
#include <iostream>
using std::ostream;
using std::streambuf;

// Constanst(s)
const unsigned short TraceManager::precision = 4;

// Variable(s)
ostream* TraceManager::trace_out = (ostream*) 0;
TraceManager* TraceManager::the_instance = (TraceManager*) 0;


//------------------------------------------------------------------------------
//
//  constructor TraceManager::TraceManager()
//
//------------------------------------------------------------------------------
TraceManager::TraceManager()
{
    trace_out = new ostream((streambuf*) 0);
//    trace_out = new ostream(cout.rdbuf());
//    *trace_out << "___";
}


//------------------------------------------------------------------------------
//
//  static TraceManager* getInstance();
//
//------------------------------------------------------------------------------
void TraceManager::initialize()
{
    if (!the_instance)
    {
        the_instance = new TraceManager();
    }
}
