/******************************************************************************

    source file AlgorithmFactory.cpp for class: AlgorithmFactory

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/



// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/AlgorithmFactory.h"
#include "Algorithm/NewMIRAAlgorithm.h"
#include "Algorithm/SMIRAAlgorithm.h"
#include "Algorithm/SamcraAfterAlgorithm.h"
#include "Algorithm/SamcraBAlgorithm.h"
#include "Algorithm/SamcraBeforeAlgorithm.h"
#include "Algorithm/ShortestPathAlgorithm.h"
#include "Algorithm/TEDBAlgorithm.h"
#include "Algorithm/WidestShortestPathAlgorithm.h"
#include "IO/Tag.h"
#include "Utils/TraceManager.h"


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor AlgorithmFactory::AlgorithmFactory()
//------------------------------------------------------------------------------
AlgorithmFactory::AlgorithmFactory()
{
  	TRACE("AlgorithmFactory::AlgorithmFactory -->");
    //Empty
  	TRACE("AlgorithmFactory::AlgorithmFactory <--");
}


//------------------------------------------------------------------------------
//  destructor AlgorithmFactory::~AlgorithmFactory()
//------------------------------------------------------------------------------
AlgorithmFactory::~AlgorithmFactory()
{
	TRACE("AlgorithmFactory::~AlgorithmFactory -->");
    //Empty
	TRACE("AlgorithmFactory::~AlgorithmFactory <--");
}


//------------------------------------------------------------------------------
//  Algorithm* create();
//------------------------------------------------------------------------------
Algorithm* AlgorithmFactory::create(const TString &description)
{
	TRACE("AlgorithmFactory::create -->");

    Algorithm* result = (Algorithm*) 0;
	if (description.empty())
	{
		ERROR("Missing information...");
		exit(-1);
	}
    if (description.front() == Tag::ALG_SHORTEST_PATH)
    {
        result = new ShortestPathAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_WIDEST_SHORTEST_PATH)
    {
        result = new WidestShortestPathAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_SAMCRA_BEFORE)
    {
        result = new SamcraBeforeAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_SAMCRA_AFTER)
    {
        result = new SamcraAfterAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_SAMCRA_B)
    {
        result = new SamcraBAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_NEW_MIRA)
    {
        result = new NewMIRAAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_SMIRA)
    {
        result = new SMIRAAlgorithm(description);
    } else
    if (description.front() == Tag::ALG_TEDB)
    {
        result = new TEDBAlgorithm(description);
    }
    else
    {
        // No matching algorithm could be found....
        ERROR("Unknown description: " << description.front());
        exit(-1);
    }

	TRACE("AlgorithmFactory::create <--");
    return result;
}
