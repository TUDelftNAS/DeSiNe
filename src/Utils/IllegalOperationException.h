#ifndef ILLEGALOPERATIONEXCEPTION_H
#define ILLEGALOPERATIONEXCEPTION_H
/******************************************************************************

    header file IllegalOperationException.h for class:
    IllegalOperationException

    This class is the base class for all illegaloperationexception used
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

class IllegalOperationException : public Exception
{
    // Constanst(s)

    // Variable(s)

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor IllegalOperationException();
//
//  Constructs IllegalOperationException.
//
//------------------------------------------------------------------------------
    IllegalOperationException(const string& message) :
        Exception(message, "IllegalOperationException")
    {
        TRACE("IllegalOperationException::IllegalOperationException -->");
        // Empty
        TRACE("IllegalOperationException::IllegalOperationException <--");
    }
};

#endif //ILLEGALOPERATIONEXCEPTION_H
