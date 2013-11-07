#ifndef WIDESTSHORTESTPATHALGORITHM_H
#define WIDESTSHORTESTPATHALGORITHM_H
/******************************************************************************

    header file WidestShortestPathAlgorithm.h for
    class: WidestShortestPathAlgorithm

    This function performs the basic Dijkstra Widest Shortest Path calculation
    on a graph in which all the links with insufficient bandwidth have been
    removed and the link metric is determined by the cost function.


    Author : T. Kleiberg
    Version: 1
    Date   : June 2004

******************************************************************************/


// Include(s)
#include "Algorithm/AbstractShortestPathAlgorithm.h"
#include "Algorithm/WSDijkstraAlgorithm.h"
#include "Utils/Types.h"
using Types::TString;


class WidestShortestPathAlgorithm : public AbstractShortestPathAlgorithm
{
    // Algorithm Factory is a concrete factory that is solely allowed to
    // instantiate new Algorithm subclasses
    friend class AlgorithmFactory;

    // Constanst(s)

    // Variable(s

    // Function(s) declarations
    protected:
//------------------------------------------------------------------------------
//
//  constructor WidestShortestPathAlgorithm();
//
//  Constructs WidestShortestPathAlgorithm with a specified topology and
//  parameters
//  Input : args: the arguments describing cost function
//  Output:
//
//------------------------------------------------------------------------------
    WidestShortestPathAlgorithm(const TString &args) :
        AbstractShortestPathAlgorithm(args)
    {
        TRACE("WidestShortestPathAlgorithm::WidestShortestPathAlgorithm -->");

        routing_alg = new WSDijkstraAlgorithm(arguments);

        TRACE("WidestShortestPathAlgorithm::WidestShortestPathAlgorithm <--");
    }
}; //end declarations
#endif //WIDESTSHORTESTPATHALGORITHM_H
