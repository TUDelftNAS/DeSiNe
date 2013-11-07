/******************************************************************************

    source file RandomVar.cpp for class: RandomVar

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "Utils/TraceManager.h"


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor RandomVar::RandomVar()
//------------------------------------------------------------------------------
RandomVar::RandomVar(RandomNumberGenerator* rng, const double &mean,
           const double &var) : rng(rng), mean(mean), variance(var)
{
    TRACE("RandomVar::RandomVar -->");
    // Empty
    TRACE("RandomVar::RandomVar <--");
}

//------------------------------------------------------------------------------
//  destructor ~RandomVar()
//------------------------------------------------------------------------------
RandomVar::~RandomVar()
{
    TRACE("RandomVar::~RandomVar -->");
    //Empty
    TRACE("RandomVar::~RandomVar <--");
}

//------------------------------------------------------------------------------
//  double getMean() const
//------------------------------------------------------------------------------
double RandomVar::getMean() const
{
    return mean;
}


//------------------------------------------------------------------------------
//  double getVariance() const
//------------------------------------------------------------------------------
double RandomVar::getVariance() const
{
    return variance;
}
