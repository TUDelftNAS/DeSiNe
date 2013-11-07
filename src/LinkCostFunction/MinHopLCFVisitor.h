#ifndef MINHOPLCFVISITOR_H
#define MINHOPLCFVISITOR_H

/******************************************************************************

    header file MinHopLCFVisitor.h for class:  MinHopLCFVisitor

    This class is meant to represent an instance of ANEV for link cost function


    Author : ***
    Version: 1
    Date   : Jan 2005

******************************************************************************/

#include "IO/Tag.h"
#include "LinkCostFunction/LinkCostFunctionVisitor.h"
#include "Network/Link.h"
#include "Utils/TraceManager.h"


class MinHopLCFVisitor : public LinkCostFunctionVisitor
{
    public:
//------------------------------------------------------------------------------
//
//  constructor MinHopLCFVisitor();
//
//  Constructs MinHopLCFVisitor. Only used by ..Factory
//
//------------------------------------------------------------------------------
    MinHopLCFVisitor()
    {
        TRACE("MinHopLCFVisitor::MinHopLCFVisitor -->");
        // empty
        TRACE("MinHopLCFVisitor::MinHopLCFVisitor <--");

    }


//------------------------------------------------------------------------------
//  ~MinHopLCFVisitor()
//
//  Destructor
//
//------------------------------------------------------------------------------
    ~MinHopLCFVisitor()
    {
        TRACE("MinHopLCFVisitor::~MinHopLCFVisitor -->");
        // empty
        TRACE("MinHopLCFVisitor::~MinHopLCFVisitor <--");
    }


//------------------------------------------------------------------------------
//  double getCost();
//
//  Compute the cost function
//
//------------------------------------------------------------------------------
    double getCost(const AbstractNetworkElement *anev) const
    {
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
        TRACE("MinHopLCFVisitor::visitLink -->");
        ((Link*) link)->setLinkCostFunctionVisitor(this);
        TRACE("MinHopLCFVisitor::visitLink <--");
    }


//------------------------------------------------------------------------------
//  string getName()
//
//  Print the visitor name
//
//------------------------------------------------------------------------------
    string getName() const
    {
        return Tag::LCF_MIN_HOP;
    }
};
#endif //MINHOPLCFVISITOR_H
