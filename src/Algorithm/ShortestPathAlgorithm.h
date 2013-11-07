#ifndef SHORTESTPATHALGORITHM_H
#define SHORTESTPATHALGORITHM_H
/******************************************************************************

    header file ShortestPathAlgorithm.h for class: ShortestPathAlgorithm

    This function performs the basic Dijkstra shortest-path calculation on a
    graph in which all the links with insufficient bandwidth have been removed
    and the link metric is determined by the cost function f.

    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/AbstractShortestPathAlgorithm.h"
#include "Algorithm/DijkstraAlgorithm.h"
#include "Utils/Types.h"
using Types::TString;


class ShortestPathAlgorithm : public AbstractShortestPathAlgorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Algorithms using ShortestPathAlgorithm
    friend class TEDBAlgorithm;

    // Constanst(s)

    // Variable(s

    protected:
//------------------------------------------------------------------------------
//
//  constructor WidestShortestPathAlgorithm();
//
//  Constructs ShortestPathAlgorithm with a specified topology and parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    ShortestPathAlgorithm(const TString &args)
        : AbstractShortestPathAlgorithm(args)
    {
        TRACE("ShortestPathAlgorithm::ShortestPathAlgorithm -->");

        routing_alg = new DijkstraAlgorithm(arguments);

        TRACE("ShortestPathAlgorithm::ShortestPathAlgorithm <--");
    }
}; //end declarations
#endif //SHORTESTPATHALGORITHM_H
