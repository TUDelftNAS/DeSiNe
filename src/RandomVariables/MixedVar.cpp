/******************************************************************************

    source file MixedVar.cpp for class: MixedVar

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "RandomVariables/MixedVar.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "Utils/TraceManager.h"
#include <ostream>
using std::ostream;

// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor MixedVar(int count, RandomVar* rvars, double* probs);
//------------------------------------------------------------------------------
MixedVar::MixedVar(RandomNumberGenerator* rng,
                   const RandomVarVector &rvars,
                   const DblVector &probs) :
    RandomVar(rng, 0.0, 0.0), ran_vars(rvars), probabilities(probs)
{
  	TRACE("MixedVar::MixedVar -->");

    // No copy is made of the RandomVar in the vector, this means that
    // they should not be deleted after the constructor has been called

    // Calculate mean and variamce
    for (usi counter = 0; counter < ran_vars.size(); ++counter)
    {
        mean += ran_vars[counter]->getMean() * probabilities[counter];
        variance += ran_vars[counter]->getVariance() *
             probabilities[counter] * probabilities[counter];
    }

  	TRACE("MixedVar::MixedVar <--");
}


//------------------------------------------------------------------------------
//  destructor MixedVar::~MixedVar()
//------------------------------------------------------------------------------
MixedVar::~MixedVar()
{
	TRACE("MixedVar::~MixedVar -->");
    for (usi counter = 0; counter < ran_vars.size(); ++counter)
    {
        delete ran_vars[counter];
    }
	TRACE("MixedVar::~MixedVar <--");
}


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void MixedVar::print(ostream &buffer) const
{
    for (usi counter = 0; counter < probabilities.size(); ++counter)
    {
        ran_vars[counter]->print(buffer);
        buffer << " " << probabilities[counter] << " ";
    }
}
