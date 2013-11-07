#ifndef MinDelayLCFVisitor_H
#define MinDelayLCFVisitor_H

/******************************************************************************

    header file MinDelayLCFVisitor.h for class:  MinDelayLCFVisitor

    This class is meant to represent an instance of ANEV for link cost function

    Minimum delay algorithm [Wang,Crowcroft - GLOBECOM 95] is a bandwidth-delay
    based routing algorithm that prunes link that do not satisfy the bandwidth
    requirement, and then finds the shortest path with respect to delay in the
    reduced path. If the delay of the shortest path is greater than the delay
    constraint, the call is not admitted.

    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class MinDelayLCFVisitor : public LinkCostFunctionVisitor
{
    public:
//------------------------------------------------------------------------------
//
//  constructor MinDelayLCFVisitor();
//
//  Constructs MinDelayLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    MinDelayLCFVisitor()
    {
        TRACE("MinDelayLCFVisitor::MinDelayLCFVisitor -->");
        // empty
        TRACE("MinDelayLCFVisitor::MinDelayLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~MinDelayLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~MinDelayLCFVisitor()
    {
        TRACE("MinDelayLCFVisitor::~MinDelayLCFVisitor -->");
        // empty
        TRACE("MinDelayLCFVisitor::~MinDelayLCFVisitor <--");
    }


//------------------------------------------------------------------------------
//  double getCost();
//
//  Compute the cost function
//
//------------------------------------------------------------------------------
    double getCost(const AbstractNetworkElement *anev) const
    {
    //	return (qos_metrics.size() > 0) ? qos_metrics[0] : 1.0;
        return 1.0;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("MinDelayLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("MinDelayLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_MIN_DELAY;
    }
};
#endif //MinDelayLCFVisitor_H
