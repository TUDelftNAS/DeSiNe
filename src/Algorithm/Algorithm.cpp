/******************************************************************************

    source file Algorithm.cpp for class: Algorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/

// Include(s)
#include "Algorithm/Algorithm.h"
#include "Utils/TraceManager.h"


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor Algorithm::Algorithm()
//------------------------------------------------------------------------------
Algorithm::Algorithm(const TString &args) : arguments(args)
{
  	TRACE("Algorithm::Algorithm -->");
	//Empty
  	TRACE("Algorithm::Algorithm <--");
}


//------------------------------------------------------------------------------
//  destructor Algorithm::~Algorithm()
//------------------------------------------------------------------------------
Algorithm::~Algorithm()
{
	TRACE("Algorithm::~Algorithm -->");
	//Empty
	TRACE("Algorithm::~Algorithm <--");
}


//------------------------------------------------------------------------------
//  void print(ostream &buffer)
//------------------------------------------------------------------------------
void Algorithm::print(ostream &buffer)
{
    if (arguments.at(0).length() > 0)
    {
        for (unsigned int iter = 0; iter < arguments.size(); ++iter)
        {
            if (iter > 0)
            {
                buffer << "_";
            }
            if (arguments.at(iter).length() > 0)
            {
                buffer << arguments.at(iter);
            }
        }
    }
}
