#ifndef SIMPLEVARIABLE_H
#define SIMPLEVARIABLE_H
/******************************************************************************

    header file SimpleVariable.h for class SimpleVariable.

    This is a class for emulating a discrete distributed variable. This is
    the simple version that only calculates the mean.

    Template class

    Author : T. Kleiberg
    Version: 1
    Date   : Jan 2005

******************************************************************************/


// Include(s)
#include "Utils/TraceManager.h"

template <typename T>
class SimpleVariable
{
    //Typedefs
    private:
    typedef long double ldouble;
    typedef unsigned long long ull;

    // Constanst(s)

    // Variable(s)
    private:
    ldouble mean; // mean
    ldouble msqr;  // mean of squares, used to calculate variance
    ull elements; // number of elements

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//  constructor SimpleVariable()
//  Constructs empty SimpleVariable.
//------------------------------------------------------------------------------
    SimpleVariable()
    {
        //TRACE("SimpleVariable::SimpleVariable -->")
        mean = 0.0;
        msqr = 0.0;
        elements = 0;
        //TRACE("SimpleVariable::SimpleVariable <--")
    }


//------------------------------------------------------------------------------
//  destructor ~SimpleVariable()
//  Destructs SimpleVariable
//------------------------------------------------------------------------------
    ~SimpleVariable()
    {
        //TRACE("SimpleVariable::~SimpleVariable -->")
        //TRACE("SimpleVariable::~SimpleVariable <--")
    }


//------------------------------------------------------------------------------
//  Add a new element to the distribution
//------------------------------------------------------------------------------
    void add(const T &var)
    {
        ++elements;
        mean += (ldouble) ((ldouble) var - mean) / elements;
        msqr += (ldouble) ((ldouble) var * var  - msqr) / elements;
    }


//------------------------------------------------------------------------------
//  Return the mean
//------------------------------------------------------------------------------
    ldouble getMean() const
    {
        TRACE("SimpleVariable::getMean -->")
        TRACE("SimpleVariable::getMean <--")
        return mean;
    }

//------------------------------------------------------------------------------
//  Return the size (number of samples)
//------------------------------------------------------------------------------
    ull getSize() const
    {
        TRACE("SimpleVariable::getSize -->")
        TRACE("SimpleVariable::getSize <--")
        return elements;
    }


//------------------------------------------------------------------------------
//  Return the variance
//------------------------------------------------------------------------------
    ldouble getVariance() const
    {
        TRACE("SimpleVariable::getVariance -->")
        ldouble result = (ldouble) msqr - mean * mean;
        TRACE("SimpleVariable::getVariance <--")
        return result;
    }


//------------------------------------------------------------------------------
//  SimpleVariable<T>& operator+=(const SimpleVariable<T>& original)
//
//  Add a SimpleVariable to the distribution
//------------------------------------------------------------------------------
    SimpleVariable<T>& operator+=(const SimpleVariable<T>& original)
    {
        TRACE("SimpleVariable::operator+= -->")
        elements += original.elements;
        mean += (ldouble) ((original.mean - mean) * original.elements) / elements;
        msqr += (ldouble) ((original.msqr - msqr) * original.elements) / elements;
        TRACE("SimpleVariable::operator+= <--")
        return *this;
    }

}; //end SimpleVariable
#endif //SIMPLEVARIABLE_H
