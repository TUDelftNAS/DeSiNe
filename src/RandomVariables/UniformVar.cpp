/******************************************************************************

    source file UniformVar.cpp for class: UniformVar

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "RandomVariables/RandomNumberGenerator.h"
#include "RandomVariables/RandomVar.h"
#include "RandomVariables/UniformVar.h"
#include "Utils/TraceManager.h"
#include <ostream>
#include <iomanip>
using std::ostream;
using std::setprecision;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor UniformVar(double min, double max)
//------------------------------------------------------------------------------
UniformVar::UniformVar(RandomNumberGenerator* rng,
                       const double &min,
                       const double &max) :
    RandomVar(rng, 0.5 * (min + max), (max - min) * (max - min) / 12.0),
    min(min), range(max - min)
{
    TRACE("UniformVar::UniformVar -->");
    //this->min = min;
    //range = max - min;
    TRACE("UniformVar::UniformVar <--");
}


//------------------------------------------------------------------------------
//  destructor UniformVar::~UniformVar()
//------------------------------------------------------------------------------
UniformVar::~UniformVar()
{
    TRACE("UniformVar::~UniformVar -->");
    // Empty
    TRACE("UniformVar::~UniformVar <--");
}

//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void UniformVar::print(ostream &buffer) const
{
    buffer << "U " << setprecision(8) << min << " " << (min + range)
           <<         setprecision(TraceManager::precision);
}
