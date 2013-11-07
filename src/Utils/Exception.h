#ifndef EXCEPTION_H
#define EXCEPTION_H
/******************************************************************************

    header file Exception.h for class: Exception

    This class is the base class for all exception used within Desine.

    Author : T. Kleiberg
    Version: 1
    Date   : Sep 2005

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"
#include <iostream>
#include <string>
//using std::cerr;
//using std::cout;
//using std::endl;
//using std::ostream;
//using std::streambuf;
using std::string;

class Exception
{
    // Constanst(s)

    // Variable(s)
    private:
    const string message, name;


    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor Exception();
//
//  Constructs Exception.
//
//------------------------------------------------------------------------------
    Exception(const string& message, string name = "Exception") :
        message(message), name(name)
    {
        TRACE("Exception::Exception -->");
        // Empty
        TRACE("Exception::Exception <--");
    }

//------------------------------------------------------------------------------
//  string getMessage() const
//
//  Returns message
//
//------------------------------------------------------------------------------
    string getMessage() const
    {
        return message;
    }


//------------------------------------------------------------------------------
//  string getName() const
//
//  Returns name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return name;
    }


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//
//  Prints Exception to the buffer
//
//------------------------------------------------------------------------------
    void print(ostream &buffer) const
    {
        buffer << name << ": " << message;
    }
};

#endif //EXCEPTION_H
