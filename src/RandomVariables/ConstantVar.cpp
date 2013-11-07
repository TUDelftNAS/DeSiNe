/******************************************************************************

    source file ConstantVar.cpp for class: ConstantVar

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : July 2006

******************************************************************************/



// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "RandomVariables/ConstantVar.h"
#include "Utils/TraceManager.h"
#include <ostream>
#include <iomanip>
using std::ostream;
using std::setprecision;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor ConstantVar(double min, double max)
//------------------------------------------------------------------------------
ConstantVar::ConstantVar(RandomNumberGenerator* rng,
                       const double &val) :
    RandomVar(rng, val, 0)
{
    TRACE("ConstantVar::ConstantVar -->");
    // Empty
    TRACE("ConstantVar::ConstantVar <--");
}


//------------------------------------------------------------------------------
//  destructor ConstantVar::~ConstantVar()
//------------------------------------------------------------------------------
ConstantVar::~ConstantVar()
{
    TRACE("ConstantVar::~ConstantVar -->");
    // Empty
    TRACE("ConstantVar::~ConstantVar <--");
}

//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void ConstantVar::print(ostream &buffer) const
{
    buffer << "C " << setprecision(8) << mean
           <<         setprecision(TraceManager::precision);
}
