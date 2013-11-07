#ifndef INVERSELCFVISITOR_H
#define INVERSELCFVISITOR_H

/******************************************************************************

    header file InverseLCFVisitor.h for class:  InverseLCFVisitor

    This class is meant to represent an instance of ANEV for link cost function


    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class InverseLCFVisitor : public LinkCostFunctionVisitor
{
    public:
//------------------------------------------------------------------------------
//
//  constructor InverseLCFVisitor();
//
//  Constructs InverseLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    InverseLCFVisitor()
    {
        TRACE("InverseLCFVisitor::InverseLCFVisitor -->");
        // empty
        TRACE("InverseLCFVisitor::InverseLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~InverseLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~InverseLCFVisitor()
    {
        TRACE("InverseLCFVisitor::~InverseLCFVisitor -->");
        // empty
        TRACE("InverseLCFVisitor::~InverseLCFVisitor <--");
    }


//------------------------------------------------------------------------------
//  double getCost();
//
//  Compute the cost function
//
//------------------------------------------------------------------------------
    double getCost(const AbstractNetworkElement *anev) const
    {
    	double result = ((Link*) anev)->getReservableCapacity();
    	return result ? 1.0/result : Link::METRIC_MIN;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("InverseLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("InverseLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_INVERSE;
    }
};
#endif //INVERSELCFVISITOR_H
