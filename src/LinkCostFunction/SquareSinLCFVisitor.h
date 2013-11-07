#ifndef SquareSinLCFVisitor_H
#define SquareSinLCFVisitor_H

/******************************************************************************

    header file SquareSinLCFVisitor.h for class:  SquareSinLCFVisitor

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


class SquareSinLCFVisitor : public LinkCostFunctionVisitor
{
    public:
//------------------------------------------------------------------------------
//
//  constructor SquareSinLCFVisitor();
//
//  Constructs SquareSinLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    SquareSinLCFVisitor()
    {
        TRACE("SquareSinLCFVisitor::SquareSinLCFVisitor -->");
        // empty
        TRACE("SquareSinLCFVisitor::SquareSinLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~SquareSinLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~SquareSinLCFVisitor()
    {
        TRACE("SquareSinLCFVisitor::~SquareSinLCFVisitor -->");
        // empty
        TRACE("SquareSinLCFVisitor::~SquareSinLCFVisitor <--");
    }


//------------------------------------------------------------------------------
//  double getCost();
//
//  Compute the cost function
//
//------------------------------------------------------------------------------
    double getCost(const AbstractNetworkElement *anev) const
    {
    	const double capacity = ((Link*) anev)->getCapacity();
    	const double x = (capacity - ((Link*) anev)->getReservableCapacity())
    	                 / capacity;
        //res = 20 * pow(sin(M_PI / 2 * x),4)  / L->capacity;
    	double result = sin(0.5 * M_PI * x);
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
        TRACE("SquareSinLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("SquareSinLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_SQUARE_SIN;
    }
};
#endif //SquareSinLCFVisitor_H
