#ifndef SMIRAALGORITHM_H
#define SMIRAALGORITHM_H
/******************************************************************************

    header file SMIRAAlgorithm.h for class: SMIRAAlgorithm

    This function performs the SMIRA calculation on a graph.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Algorithm/WSDijkstraAlgorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Utils/Types.h"
using Types::TString;
#include <sstream>

class SMIRAAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s
    protected:
    Algorithm *dijkstra_alg;
    WSDijkstraAlgorithm *wsdijkstra_alg;


    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor SMIRAAlgorithm();
//
//  Constructs SMIRAAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    SMIRAAlgorithm(const TString &args);

    public:
//------------------------------------------------------------------------------
//
//  destructor ~SMIRAAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~SMIRAAlgorithm();


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
#endif //SMIRAALGORITHM_H
