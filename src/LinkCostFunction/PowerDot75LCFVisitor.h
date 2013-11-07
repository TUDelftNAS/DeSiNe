#ifndef PowerDot75LCFVisitor_H
#define PowerDot75LCFVisitor_H

/******************************************************************************

    header file PowerDot75LCFVisitor.h for class:  PowerDot75LCFVisitor

    This class is meant to represent an instance of ANEV for link cost function

    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"
#include <cmath>


class PowerDot75LCFVisitor : public LinkCostFunctionVisitor
{
    public:
//------------------------------------------------------------------------------
//
//  constructor PowerDot75LCFVisitor();
//
//  Constructs PowerDot75LCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    PowerDot75LCFVisitor()
    {
        TRACE("PowerDot75LCFVisitor::PowerDot75LCFVisitor -->");
        // empty
        TRACE("PowerDot75LCFVisitor::PowerDot75LCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~PowerDot75LCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~PowerDot75LCFVisitor()
    {
        TRACE("PowerDot75LCFVisitor::~PowerDot75LCFVisitor -->");
        // empty
        TRACE("PowerDot75LCFVisitor::~PowerDot75LCFVisitor <--");
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
    	return result ? pow(result, -0.75) : Link::METRIC_MAX;
    }


//------------------------------------------------------------------------------
//  void visitLink(const AbstractNetworkElement& link)
//
//  See AbstractNetworkElementVisitor for detais
//
//------------------------------------------------------------------------------
    void visitLink(const AbstractNetworkElement* link)
    {
        TRACE("PowerDot75LCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("PowerDot75LCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_PWRDOT75;
    }
};
#endif //PowerDot75LCFVisitor_H
