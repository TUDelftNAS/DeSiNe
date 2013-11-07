/******************************************************************************

    source file ExponentialVar.cpp for class: ExponentialVar

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : Feb 2005

******************************************************************************/



// Include(s)
#include "RandomVariables/ExponentialVar.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/TraceManager.h"
#include <ostream>
#include <iomanip>
using std::ostream;
using std::setprecision;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor ExponentialVar(double mean)
//------------------------------------------------------------------------------
ExponentialVar::ExponentialVar(RandomNumberGenerator* rng,
                               const double &mean) :
    RandomVar(rng, mean, mean * mean)
{
    TRACE("ExponentialVar::ExponentialVar -->");
    if (!mean)
    {
        WARNING("Trying to create a exponential random variable with mean 0");
    }
    TRACE("ExponentialVar::ExponentialVar <--");
}


//------------------------------------------------------------------------------
//  destructor ExponentialVar::~ExponentialVar()
//------------------------------------------------------------------------------
ExponentialVar::~ExponentialVar()
{
    TRACE("ExponentialVar::~ExponentialVar -->");
    //Empty
    TRACE("ExponentialVar::~ExponentialVar <--");
}


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void ExponentialVar::print(ostream &buffer) const
{
    buffer << "E " << setprecision(12) << mean
           <<         setprecision(TraceManager::precision);
}
