#ifndef DELTALCFVISITOR_H
#define DELTALCFVISITOR_H

/******************************************************************************

    header file DeltaLCFVisitor.h for class:  DeltaLCFVisitor

    This class is meant to represent an instance of ANEV for link cost function


    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class DeltaLCFVisitor : public LinkCostFunctionVisitor
{
    private:
    static const double DELTA = 0.6;
    static const double FDELTA = 1.5;

    public:
//------------------------------------------------------------------------------
//
//  constructor DeltaLCFVisitor();
//
//  Constructs DeltaLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    DeltaLCFVisitor()
    {
        TRACE("DeltaLCFVisitor::DeltaLCFVisitor -->");
        // empty
        TRACE("DeltaLCFVisitor::DeltaLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~DeltaLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~DeltaLCFVisitor()
    {
        TRACE("DeltaLCFVisitor::~DeltaLCFVisitor -->");
        // empty
        TRACE("DeltaLCFVisitor::~DeltaLCFVisitor <--");
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
    	const double x = ( capacity - ((Link*) anev)->getReservableCapacity())
    	                  / capacity;
        if (x != 0.0)
        {
        	if (x < DELTA)
        	{
        		result = 1.0 + x * (FDELTA - 1.0) / DELTA;
        	}
        	else
        	{
        		result = FDELTA * (1.0 - DELTA) / (1.0 - x);
            }
        } // end: if (x != 0.0)
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
        TRACE("DeltaLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("DeltaLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_DELTA;
    }
};
#endif //DELTALCFVISITOR_H
