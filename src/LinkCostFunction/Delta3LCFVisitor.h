#ifndef DELTA3LCFVISITOR_H
#define DELTA3LCFVISITOR_H

/******************************************************************************

    header file Delta3LCFVisitor.h for class:  Delta3LCFVisitor

    This class is meant to represent an instance of ANEV for link cost function


    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class Delta3LCFVisitor : public LinkCostFunctionVisitor
{
    private:
    static const double DELTA  = 0.75;
    static const double DELTA3 = 0.421875; //0.75^3 = 0.421875
	static const double FDELTA = 1.5;

    public:
//------------------------------------------------------------------------------
//
//  constructor Delta3LCFVisitor();
//
//  Constructs Delta3LCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    Delta3LCFVisitor()
    {
        TRACE("Delta3LCFVisitor::Delta3LCFVisitor -->");
        // empty
        TRACE("Delta3LCFVisitor::Delta3LCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~Delta3LCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~Delta3LCFVisitor()
    {
        TRACE("Delta3LCFVisitor::~Delta3LCFVisitor -->");
        // empty
        TRACE("Delta3LCFVisitor::~Delta3LCFVisitor <--");
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
        		result = x * x * x * FDELTA / DELTA3;
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
        TRACE("Delta3LCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("Delta3LCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_DELTA3;
    }

};
#endif //DELTA3LCFVISITOR_H
