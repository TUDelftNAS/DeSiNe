#ifndef TEDBLCFVisitor_H
#define TEDBLCFVisitor_H

/******************************************************************************

    header file TEDBLCFVisitor.h for class:  TEDBLCFVisitor

    This class is meant to represent an instance of ANEV for link cost function

    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class TEDBLCFVisitor : public LinkCostFunctionVisitor
{
    private:
    static const double BOUND = 0.5;

    public:
//------------------------------------------------------------------------------
//
//  constructor TEDBLCFVisitor();
//
//  Constructs TEDBLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    TEDBLCFVisitor()
    {
        TRACE("TEDBLCFVisitor::TEDBLCFVisitor -->");
        // empty
        TRACE("TEDBLCFVisitor::TEDBLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~TEDBLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~TEDBLCFVisitor()
    {
        TRACE("TEDBLCFVisitor::~TEDBLCFVisitor -->");
        // empty
        TRACE("TEDBLCFVisitor::~TEDBLCFVisitor <--");
    }


//------------------------------------------------------------------------------
//  double getCost();
//
//  Compute the cost function
//
//------------------------------------------------------------------------------
    double getCost(const AbstractNetworkElement *anev) const
    {
        double result = 0.0;
        const double capacity = ((Link*) anev)->getCapacity();
        const double x = (capacity - ((Link*) anev)->getReservableCapacity())
                         / capacity;
        if (x > BOUND)
        {
            result = (x - BOUND) / (1.0 - x);
        }
        return result ? result : Link::METRIC_MIN;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("TEDBLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("TEDBLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_TEDB;
    }
};
#endif //TEDBLCFVisitor_H
