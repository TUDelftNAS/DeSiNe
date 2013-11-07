#ifndef ABSTRACTSHORTESTPATHALGORITHM_H
#define ABSTRACTSHORTESTPATHALGORITHM_H
/******************************************************************************

    header file AbstractShortestPathAlgorithm.h for class:
      AbstractShortestPathAlgorithm

    This class forms an abstract base class for the shortest path algorihms. It
    resembles the Template Method design pattern. Subclasses must instantiate the
    routing_alg object that forms the actual class that performs the algorithm.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
using Types::TString;


class AbstractShortestPathAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s
    protected:
    Algorithm* routing_alg;

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor AbstractShortestPathAlgorithm();
//
//  Constructs AbstractShortestPathAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    AbstractShortestPathAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~AbstractShortestPathAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~AbstractShortestPathAlgorithm();


//------------------------------------------------------------------------------
//  Path compute(const Flow &flow)
//
//  Computes the Path for a given flow according to the implementation of the
//  algorithm.
//  Input : the flow for which to find a path
//  Output:
//      - : the calculated path
//------------------------------------------------------------------------------
    Path compute(const Flow &flow);

}; //end declarations
#endif //ABSTRACTSHORTESTPATHALGORITHM_H
