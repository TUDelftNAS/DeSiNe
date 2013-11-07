#ifndef WSDIJKSTRAALGORITHM_H
#define WSDIJKSTRAALGORITHM_H
/******************************************************************************

    header file WSDijkstraAlgorithm.h for class: WSDijkstraAlgorithm

    This class implements the base-class Algorithm for a Dijkstra Widest
    Shortest Path implementation. It defines two distance functions: one is
    based on link metric, the other is the maximal reservable bandwidth (mrb)
    of the path. When selecting the next node to mark, one selects the node
    with the minimal length. If several nodes have the same minimal length, one
    selects the node with the largest mrb.

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


class WSDijkstraAlgorithm : public Algorithm
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
//  constructor WSDijkstraAlgorithm();
//
//  Constructs WSDijkstraAlgorithm with a specified topology and parameters
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    WSDijkstraAlgorithm(const TString &args);


//------------------------------------------------------------------------------
//
//  destructor ~WSDijkstraAlgorithm()
//  Input :
//  Output:
//
//------------------------------------------------------------------------------
    ~WSDijkstraAlgorithm();


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
#endif //WSDIJKSTRAALGORITHM_H
