#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H
/******************************************************************************

    header file DijkstraAlgorithm.h for class: DijkstraAlgorithm

    This class implements the base-class Algorithm for a Dijkstra Shortest
    Path implementation.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "RandomVariables/RandomNumberGenerator.h"
#include "Utils/Types.h"
using Types::TString;


class DijkstraAlgorithm : public Algorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s)
    private:
    RandomNumberGenerator* rng;

    // Function(s) declarations
    public:
//------------------------------------------------------------------------------
//
//  constructor DijkstraAlgorithm();
//
//  Constructs DijkstraAlgorithm with a specified topology and parameters
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
   DijkstraAlgorithm(const TString &args);


//------------------------------------------------------------------------------
//
//  destructor ~DijkstraAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    virtual ~DijkstraAlgorithm();


//------------------------------------------------------------------------------
//  Path compute(const Flow &flow)
//
//  Computes the Path for a given flow according to the implementation of the
//  algorithm.
//  Input : the flow for which to find a path
//  Output:
//      - : the calculated path
//------------------------------------------------------------------------------
    Path compute(const Flow &flow)
    {
        return compute(flow.getSource(), flow.getDestination(),
                       flow.getTopology());
    }


//------------------------------------------------------------------------------
//  Path compute(const int source, int destination)
//
//  Computes the Path for a given source and destination pair
//  Input : s & d
//  Output:
//      - : the calculated path
//------------------------------------------------------------------------------
    Path compute(const int &flow_source, const int &flow_destination,
                 Topology* topology);

}; //end declarations
#endif //DIJKSTRAALGORITHM_H
