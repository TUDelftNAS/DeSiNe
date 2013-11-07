#ifndef INSUFFICIENTCAPACITYEXCEPTION_H
#define INSUFFICIENTCAPACITYEXCEPTION_H
/******************************************************************************

    header file InsufficientCapacityException.h for class:
    InsufficientCapacityException

    This class is the base class for all insufficientcapacityexception used
    within Desine.

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2005

******************************************************************************/


// Include(s)
#include "Utils/Exception.h"
#include <iostream>
#include <string>
//using std::cerr;
//using std::cout;
//using std::endl;
//using std::ostream;
//using std::streambuf;
using std::string;

class InsufficientCapacityException : public Exception
{
    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor InsufficientCapacityException();
//
//  Constructs InsufficientCapacityException.
//
//------------------------------------------------------------------------------
    InsufficientCapacityException(const string& message) :
        Exception(message, "InsufficientCapacityException")
    {
        TRACE("InsufficientCapacityException::InsufficientCapacityException -->");
        // Empty
        TRACE("InsufficientCapacityException::InsufficientCapacityException <--");
    }
};
#endif //INSUFFICIENTCAPACITYEXCEPTION_H
