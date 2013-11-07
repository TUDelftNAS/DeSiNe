/******************************************************************************

    source file AbstractShortestPathAlgorithm.cpp for class:
        AbstractShortestPathAlgorithm

    See header file for details

    Author : T. Kleiberg
    Version: 1
    Date   : August 2004

******************************************************************************/



// Include(s)
#include "Algorithm/AbstractShortestPathAlgorithm.h"
#include "Algorithm/Algorithm.h"
#include "Network/Flow.h"
#include "Network/LinkList.h"
#include "Network/Path.h"
#include "Network/Topology.h"
#include "Utils/Timer.h"
#include "Utils/TraceManager.h"


// Constanst(s)

// Variable(s)

// Function(s) definitions

//------------------------------------------------------------------------------
//  constructor AbstractShortestPathAlgorithm::AbstractShortestPathAlgorithm()
//------------------------------------------------------------------------------
AbstractShortestPathAlgorithm::AbstractShortestPathAlgorithm(const TString &args)
    : Algorithm(args)
{
    TRACE("AbstractShortestPathAlgorithm::AbstractShortestPathAlgorithm -->");
    // Empty
    TRACE("AbstractShortestPathAlgorithm::AbstractShortestPathAlgorithm <--");
}


//------------------------------------------------------------------------------
//  destructor AbstractShortestPathAlgorithm::~AbstractShortestPathAlgorithm()
//------------------------------------------------------------------------------
AbstractShortestPathAlgorithm::~AbstractShortestPathAlgorithm()
{
    TRACE("AbstractShortestPathAlgorithm::~AbstractShortestPathAlgorithm -->");
    if (routing_alg) delete routing_alg;
    TRACE("AbstractShortestPathAlgorithm::~AbstractShortestPathAlgorithm <--");
}


//------------------------------------------------------------------------------
//  Path* AbstractShortestPathAlgorithm::compute(Flow* flow)
//------------------------------------------------------------------------------
Path AbstractShortestPathAlgorithm::compute(const Flow &flow)
{
    TRACE("AbstractShortestPathAlgorithm::compute -->");

    Path result;
    Topology *topology = flow.getTopology();

    // Set link cost function
    // it is assumed that args second word is the linkcostfunction ID
    // if not, unexpected results may occur
    topology->setLinkCostFunction(arguments.at(1));


//    flow.print(logid);

    // pruning of the links with insufficient bandwidth and
    // setting up the link metric
    for (LinkListIterator iter = topology->getLinkIterator(); iter(); ++iter)
    {
        Link* link = *iter;
        if (link->getReservableCapacity() < flow.getRequestedCapacity())
        {
            link->metric=-1.0;
        }
        else
        {
            link->metric=link->getCost();
        }
    }

#ifndef NO_TIMER
    Timer timer;
    timer.start();
#endif // NO_TIMER
    result = routing_alg->compute(flow);
#ifndef NO_TIMER
    const_cast<Flow&>(flow).setTime(timer.read());
#endif // NO_TIMER

    TRACE("AbstractShortestPathAlgorithm::compute <--");
    return result;
}
